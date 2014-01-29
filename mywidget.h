#pragma once

#include "glheader.h"
#include <QGLWidget>
#include <QTimer>

#include "voxelizer.h"

class Voxelizer;

class MyWidget : public QGLWidget
{
    Q_OBJECT
public:
    MyWidget( const QGLFormat& format, std::unique_ptr<Voxelizer>&& voxelizer, QWidget* parent = 0 );

protected:
    virtual void initializeGL();
    virtual void resizeGL( int w, int h );
    virtual void paintGL();
    void keyPressEvent(QKeyEvent *event);
private:
    GLuint prepareShaderProgram( const QString& vertexShaderPath,
                               const QString& fragmentShaderPath );
    void updateData();
    void updateTitle();
    GLuint m_shader;
    GLuint  vertexBuffer;
    GLuint m_vertexBuffer;
    std::unique_ptr<Voxelizer> voxelizer;
    int triangels;
    QTimer *m_timer_p;
};

