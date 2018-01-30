#include "ball.h"
#include "main.h"

Ball::Ball(float x, float y, float size, int shape, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.01;
    acceleration = 0.0080;
    speedy = 0;
    this->master = 0;
    int n=45; //circle
    float angle=360/n;
    if(shape==-1) angle=180/n;
    int i=0,j=0;
    static GLfloat vertex_buffer_data[1000];
    for(i=0;i<n;i++)
    {
        //first vertex
        vertex_buffer_data[j]=shape*cos(angle*i*3.14/180)*size/5;
        vertex_buffer_data[j+1]=shape*sin(angle*i*3.14/180)*size/5;
        vertex_buffer_data[j+2]=0.0f;

        //second vertex
        vertex_buffer_data[j+3]=0.0f;
        vertex_buffer_data[j+4]=0.0f;
        vertex_buffer_data[j+5]=0.0f;
        j+=6;

        //third vertex
        vertex_buffer_data[j]=shape*cos(angle*(i+1)*3.14/180)*size/5;
        vertex_buffer_data[j+1]=shape*sin(angle*(i+1)*3.14/180)*size/5;
        vertex_buffer_data[j+2]=0.0f;
        j+=3;

    }

    this->object = create3DObject(GL_TRIANGLES, 1000, vertex_buffer_data, color, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::tick() {
    this->position.x -= speed;
    if(this->master == 0 && this->position.x > 4){
        this->position.x=-4;
        this->speed = -1*RandomNumber(0.005,0.05);
        this->position.y = RandomNumber(1,3);
    }
    if(this->master == 1){
    if(this->position.x > 4){
        this->position.x=-4;        
    }
    if(this->position.x < -4){
        this->position.x=4;        
    }
    }
    // this->position.y -= speed;
    //if(this->position.y <-1 )this->position.y = -1;
    //if(this->speedy == 0 && this->position.y>-1)position.y = -1;
}

bounding_box_t Ball::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.4, 0.4 };
    return bbox;
}
