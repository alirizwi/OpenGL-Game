#include "rectangle.h"
#include "main.h"

Rectangle::Rectangle(float x, float y, float l, float b, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.05;
//    acceleration = 0.0080;
 //   speedy = 0;
    const GLfloat vertex_buffer_data[] = {
        -l/2, -b/2, 0, // vertex 1
        l/2,  -b/2, 0, // vertex 2
        l/2,  b/2, 0, // vertex 3

        l/2,  b/2, 0, // vertex 3
        -l/2, b/2, 0, // vertex 4
        -l/2, -b/2, 0 // vertex 1
    };

    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);
}

void Rectangle::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate  = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Rectangle::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Rectangle::tick() {
    if(this->position.y <-3 )this->position.y = -3;
//    if(this->speedy == 0 && this->position.y>-3)position.y = -3;
}

bounding_box_t Rectangle::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.4, 0.4 };
    return bbox;
}
