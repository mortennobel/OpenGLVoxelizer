#include "mywidget.h"
#include <QApplication>
#include <QtGui>
#include <voxelizer.h>

using namespace glm;

int main(int argc, char *argv[])
{
    QApplication a( argc, argv );

    auto sphere = [](ivec3 pos){
        int x = pos[0], y =  pos[1], z = pos[2];
        float radius = 9.00f;
        return (float)std::sqrt(x*x + y*y + z*z)-radius;
    };

    std::unique_ptr<Voxelizer> voxelizer = std::unique_ptr<Voxelizer>(new Voxelizer(sphere, glm::ivec3{-10}, glm::ivec3{11}, glm::ivec3{1,1,1}));

    QGLFormat glFormat;
    glFormat.setVersion( 3, 2 );
    glFormat.setProfile( QGLFormat::CoreProfile );
    glFormat.setSampleBuffers( false );
    glFormat.setDepth(true);
    glFormat.setDepthBufferSize(16);
    MyWidget w( glFormat, move(voxelizer) );
    w.show();

    return a.exec();
}
