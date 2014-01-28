#include "mywidget.h"
#include <QApplication>
#include <QtGui>
#include <voxelizer.h>

int main(int argc, char *argv[])
{
    QApplication a( argc, argv );

    auto sphere = [](vec3i pos){
        int x = pos[0], y =  pos[1], z = pos[2];
        float radius = 8.0f;
        return (float)sqrt(x*x + y*y + z*z)-radius;
    };

    Voxelizer voxelizer(sphere);

    QGLFormat glFormat;
    glFormat.setVersion( 3, 2 );
    glFormat.setProfile( QGLFormat::CoreProfile );
    glFormat.setSampleBuffers( false );
    glFormat.setDepth(true);
    glFormat.setDepthBufferSize(16);
    MyWidget w( glFormat, &voxelizer );
    w.show();

    return a.exec();
}
