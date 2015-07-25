#ifndef SCENE_H
#define SCENE_H

//#include <GL/glew.h>
#include "glextensions.h"

#include <QtWidgets>
#include <QtOpenGL>

#include "roundedbox.h"
#include "gltrianglemesh.h"
#include "trackball.h"
#include "glbuffers.h"
#include "qtbox.h"

#define PI 3.14159265358979

QT_BEGIN_NAMESPACE
class QMatrix4x4;
QT_END_NAMESPACE

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    Scene(int width, int height, int maxTextureSize);
    ~Scene();
    virtual void drawBackground(QPainter *painter, const QRectF &rect) Q_DECL_OVERRIDE;

public slots:
    void setShader(int index);
    void setTexture(int index);

protected:
    void renderObjects(const QMatrix4x4 &view);
    void setStates();
    void setLights();
    void defaultStates();

    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    virtual void wheelEvent(QGraphicsSceneWheelEvent * event) Q_DECL_OVERRIDE;
private:
    void initGL();
    QPointF pixelPosToViewPos(const QPointF& p);

    QTime m_time;
    int m_lastTime;
    int m_mouseEventTime;
    int m_distExp;
    int m_frame;
    int m_maxTextureSize;
    int m_currentShaderId;
    int m_currentTextureId;

    QTimer *m_timer;
    GLRoundedBox *m_box;

    TrackBall m_TrackBallModels;
    TrackBall m_TrackBallDrag;
    TrackBall m_TrackBallCamera;

    QVector<GLTexture *> m_vecPTextures;
    GLTextureCube *m_pEnvCubeTexture;
    QVector<QGLShaderProgram *> m_vecPShaderPrograms;
    QGLShader *m_pVertexShader;
    QVector<QGLShader *> m_vecPFraShaders;
    QGLShader *m_pEnvFragShader;
    QGLShaderProgram *m_pEnvShaderProgram;
};

#endif
