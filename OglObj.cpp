/*  This file is part of TSRE5.
 *
 *  TSRE5 - train sim game engine and MSTS/OR Editors. 
 *  Copyright (C) 2016 Piotr Gadecki <pgadecki@gmail.com>
 *
 *  Licensed under GNU General Public License 3.0 or later. 
 *
 *  See LICENSE.md or https://www.gnu.org/licenses/gpl.html
 */

#include "OglObj.h"
#include "TexLib.h"
#include "Game.h"
#include "GLMatrix.h"

OglObj::OglObj() {
    loaded = false;
    texId = -1;
    materialType = NONE;
}

OglObj::OglObj(const OglObj& orig) {
}

OglObj::~OglObj() {

}

void OglObj::setMaterial(float r, float g, float b) {
    materialType = COLOR;
    if(color == NULL) {
        color = new Vector4f(r, g, b, 1.0);
    } else {
        color->x = r;
        color->y = g;
        color->z = b;
        color->c = 1.0;
    }
}

void OglObj::setMaterial(QString* path) {
    materialType = TEXTURE;
    res = path;
}

void OglObj::deleteVBO(){
    if(loaded){
        VBO.destroy();
        VAO.destroy();
    }
    loaded = false;
}

void OglObj::init(float* punkty, int ptr, enum VertexAttr v, int type) {
    //if(loaded){
    //    VBO.destroy();
    //    VAO.destroy();
    //}
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    shapeType = type;
    vAttribures = v;
    if(!loaded){
        VAO.create();
        VBO.create();
    }
    QOpenGLVertexArrayObject::Binder vaoBinder(&VAO);
    VBO.bind();
    VBO.allocate(punkty, ptr * sizeof (GLfloat));
    
    if (v == V) {
        f->glEnableVertexAttribArray(0);
        f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof (GLfloat), 0);
    } else if (v == VT) {
        f->glEnableVertexAttribArray(0);
        f->glEnableVertexAttribArray(1);
        f->glEnableVertexAttribArray(3);
        f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof (GLfloat), 0);
        f->glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 6 * sizeof (GLfloat), reinterpret_cast<void *> (3 * sizeof (GLfloat)));
        f->glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 6 * sizeof (GLfloat), reinterpret_cast<void *> (5 * sizeof (GLfloat)));
    } else if (v == VNT) {
        f->glEnableVertexAttribArray(0);
        f->glEnableVertexAttribArray(1);
        f->glEnableVertexAttribArray(2);
        f->glEnableVertexAttribArray(3);
        f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof (GLfloat), 0);
        f->glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof (GLfloat), reinterpret_cast<void *> (3 * sizeof (GLfloat)));
        f->glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 9 * sizeof (GLfloat), reinterpret_cast<void *> (6 * sizeof (GLfloat)));
        f->glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 9 * sizeof (GLfloat), reinterpret_cast<void *> (8 * sizeof (GLfloat)));
    }
    
    VBO.release();
    length = ptr / v;
    loaded = true;
}

void OglObj::setLineWidth(int val){
    lineWidth = val;
}

void OglObj::render() {
    render(0);
}

void OglObj::render(int selectionColor) {
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    GLUU *gluu = GLUU::get();
    
    if(vAttribures == NO_ATTR){
        return;
    } else if(vAttribures == V){
        gluu->disableNormals();
    } else if(vAttribures == VT){
        gluu->disableNormals();
    } else if(vAttribures == VNT){
        gluu->enableNormals();
    }  
    
    if(selectionColor != 0){
        int wColor = (int)(selectionColor/65536);
        int sColor = (int)(selectionColor - wColor*65536)/256;
        int bColor = (int)(selectionColor - wColor*65536 - sColor*256);
        gluu->disableTextures((float)wColor/255.0f, (float)sColor/255.0f, (float)bColor/255.0f, 1);
    } else if(materialType == TEXTURE){
        gluu->enableTextures();
        if (texId == -2) {
            return;
        } else {
            if (texId == -1) {
                texId = TexLib::addTex(*res);
                //qDebug() << texId << " "<< *res;
            }
            if (TexLib::mtex[texId]->loaded) {
                if (!TexLib::mtex[texId]->glLoaded)
                    TexLib::mtex[texId]->GLTextures();
                f->glBindTexture(GL_TEXTURE_2D, TexLib::mtex[texId]->tex[0]);
            } else {
            }
        }
    } else if(materialType == COLOR){
        gluu->disableTextures(color);
    } else if(materialType == NONE){
        return;
    }

    if(lineWidth > 0 && lineWidth != Game::oglDefaultLineWidth)
        f->glLineWidth(lineWidth);
    gluu->currentShader->setUniformValue(gluu->currentShader->msMatrixUniform, *reinterpret_cast<float(*)[4][4]>(gluu->objStrMatrix));
    gluu->currentMsMatrinxHash = gluu->getMatrixHash(gluu->objStrMatrix);
    QOpenGLVertexArrayObject::Binder vaoBinder(&VAO);
    f->glDrawArrays(shapeType, 0, length); /**/
    
    if(lineWidth > 0 && lineWidth != Game::oglDefaultLineWidth)
        f->glLineWidth(Game::oglDefaultLineWidth);
}

int OglObj::getTexId(){
    return this->texId;
}