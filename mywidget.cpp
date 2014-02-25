#include "mywidget.h"

#include <QDebug>
#include <QKeyEvent>
#include <QFile>
#include <QString>

#include <iostream>
#include <memory>
#include <vector>
#include <cmath>

using namespace std;

MyWidget::MyWidget( const QGLFormat& format, std::unique_ptr<Voxelizer>&& voxelizer, QWidget* parent )
    : QGLWidget( format, parent ),
      m_vertexBuffer( 0 ), voxelizer(std::move(voxelizer)), m_timer_p( new QTimer( this ) )
{
    // When the timer goes off, run our function to change the t value.
    connect( m_timer_p, SIGNAL( timeout() ), SLOT( update() ) );
    // Start the timer to go off every TIMER_INTERVAL milliseconds
    m_timer_p->start( 16 );


}

void MyWidget::keyPressEvent(QKeyEvent *event){
    if (event->type() == event->Type::KeyPress){
        switch (event->key()){
        case '0':
            voxelizer->setInterpolation(Interpolation::Analytic);
        break;
        case '1':
            voxelizer->setInterpolation(Interpolation::ComponentWiseLinear);
        break;
        case '2':
            voxelizer->setInterpolation(Interpolation::Linear);
        break;
        case '3':
            voxelizer->setInterpolation(Interpolation::Sobel);
        break;
        }
        updateData();
    }
}

GLuint MyWidget::prepareShaderProgram( const QString& vertexShaderPath,
                                     const QString& fragmentShaderPath )
{
    struct Shader {
        const QString&  filename;
        GLenum       type;
        GLchar*      source;
    }  shaders[2] = {
        { vertexShaderPath, GL_VERTEX_SHADER, NULL },
        { fragmentShaderPath, GL_FRAGMENT_SHADER, NULL }
    };

    GLuint program = glCreateProgram();

    for ( int i = 0; i < 2; ++i ) {
        Shader& s = shaders[i];
        QFile file( s.filename );
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            qWarning() << "Cannot open file " << s.filename;
            exit( EXIT_FAILURE );
        }
        QByteArray data = file.readAll();
        file.close();
        s.source = data.data();

        if ( shaders[i].source == NULL ) {
            qWarning() << "Failed to read " << s.filename;
            exit( EXIT_FAILURE );
        }
        GLuint shader = glCreateShader( s.type );
        glShaderSource( shader, 1, (const GLchar**) &s.source, NULL );
        glCompileShader( shader );

        GLint  compiled;
        glGetShaderiv( shader, GL_COMPILE_STATUS, &compiled );
        if ( !compiled ) {
            qWarning() << s.filename << " failed to compile:" ;
            GLint  logSize;
            glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &logSize );
            auto logMsg = unique_ptr<char>(new char[logSize]);
            glGetShaderInfoLog( shader, logSize, NULL, logMsg.get() );
            qWarning() << logMsg.get();

            exit( EXIT_FAILURE );
        }

        glAttachShader( program, shader );
    }

    // Link output
    glBindFragDataLocation(program, 0, "fragColor");

    // link  and error check
    glLinkProgram(program);

    GLint  linked;
    glGetProgramiv( program, GL_LINK_STATUS, &linked );
    if ( !linked ) {
        qWarning() << "Shader program failed to link";
        GLint  logSize;
        glGetProgramiv( program, GL_INFO_LOG_LENGTH, &logSize);
        char* logMsg = new char[logSize];
        glGetProgramInfoLog( program, logSize, NULL, logMsg );
        qWarning() << logMsg ;
        delete [] logMsg;

        exit( EXIT_FAILURE );
    }

    // use program object
    glUseProgram(program);

    return program;
}

void MyWidget::updateData(){
    vector<float> points = voxelizer->getData();
    int sizeOfVertex = 6;
    triangels = points.size()/sizeOfVertex;
    glBindVertexArray(m_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, triangels * sizeOfVertex * sizeof(float), &(points[0]), GL_STATIC_DRAW);
    GLuint positionAttribute = glGetAttribLocation(m_shader, "vertex");
    GLuint normalAttribute = glGetAttribLocation(m_shader, "normal");
    glEnableVertexAttribArray(positionAttribute);
    glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(float)*sizeOfVertex, (const GLvoid *)0);
    glEnableVertexAttribArray(normalAttribute);
    glVertexAttribPointer(normalAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(float)*sizeOfVertex, (const GLvoid *)(sizeof(float)*3));
    updateTitle();
}

void MyWidget::updateTitle(){
    QString title = "";
    QString titles[] = {
        "Analytic",
        "Component-wise Linear",
        "Linear",
        "Sobel"
    };
    for (int i=0;i<4;i++){
        if (static_cast<int>(voxelizer->getInterpolation())==i){
            title = title +"["+('0'+i)+"] ";
        } else {
            title = title +" "+('0'+i)+"  ";
        }
        title = title + titles[i]+"  ";
    }
    QWidget::setWindowTitle(title);
}

void MyWidget::initializeGL()
{
    glSetup();
    glEnable(GL_DEPTH_TEST);
    // Prepare a complete shader program...
    m_shader = prepareShaderProgram( ":/simple.vert", ":/simple.frag" );

    glGenVertexArrays(1, &m_vertexBuffer);
    glGenBuffers(1, &vertexBuffer);
    updateData();
}

void MyWidget::resizeGL( int w, int h )
{
    // Set the viewport to window dimensions
    glViewport( 0, 0, w, qMax( h, 1 ) );
}

void MyWidget::paintGL()
{
    // Clear the buffer with the current clearing color
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // set uniforms
    GLint mvpLocation = glGetUniformLocation(m_shader, "mvp");
    float scale = 0.1;
    static float timer = 0;
    timer += 0.016;
    float mvp[] = { // model view projection
        cos(timer)*scale,0.0f,sin(timer)*scale,0.0f,
        0.0f,scale,0.0f,0.0f,
        -sin(timer)*scale,0.0f,cos(timer)*scale,0.0f,
        0.0f,0.0f,0.0f,1.0f
    };
    glUniformMatrix4fv(mvpLocation, 1, false, mvp);

    // Draw stuff
    glDrawArrays( GL_TRIANGLES, 0, triangels  );
}

