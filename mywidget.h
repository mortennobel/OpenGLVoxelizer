#pragma once

#include <QGLWidget>
#include <QTimer>

#include "voxelizer.h"
#include <QOpenGLFunctions_3_2_Core>

class Voxelizer;

class MyWidget : public QGLWidget, protected QOpenGLFunctions_3_2_Core
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
    GLuint vertexArrayObject;
    GLuint  vertexBuffer;
    GLuint  elementIndexBuffer;

    std::unique_ptr<Voxelizer> voxelizer;
    int triangels;
    int vertexIndices;
    QTimer *m_timer_p;
};

