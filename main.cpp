 #include<windows.h>
#include<GL/freeglut.h>
#include<math.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#define MAX_STARS 55
#define MAX_SNOW 120
#define PI 3.14159265f

float Angle = 0.0f; //Cloud Angle
float Angle_tree = 0.0f;
float Angle_rock = 0.5f;
float speed_cloud = 0.005f;
float speed_Tree = 0.015f;
float speed_rock = 0.005f;
float car = 0.0f; // Player car
float enemy_y = 0.8f;
float enemy_x = 0.0f;
float score = 0;
float sunY = 1.5f;
float moonY = -1.5f;
float speed_sun_moon = 0.005f;
float enemy_speed = 0.01f;


int isGameOver = 0;

int gameStarted = 0;



//Scene Type Variable

int sceneType = 0; // 0=Green Field, 1=Desert, 2=City, 3=Village, 4=Snow Night

float sceneTimer  = 0.0f;

float desertTimer = 15.0f;



// City and village scene variable

float cloudX   = -0.2f;

float sideMove =  0.0f;

// New city environment variables (only for city scene)
float cityCloudX = -0.8f;
float cityDarkCloudX = -1.4f;
float cityRainY = 0.0f;
float cityBirdX = -1.2f;
float citySideMove = 0.0f;
float citySunAngle = 0.0f;
int cityTimeCount = 0;
bool cityRainStart = false;



// Snow- orpa

float snowX[MAX_SNOW];
float snowY_arr[MAX_SNOW];
float snowSpeed[MAX_SNOW];
float snowDriftX[MAX_SNOW];
float cloudAnim = 0.0f;
float lampAnim  = 0.0f;
float treeAnim  = 0.0f;
float starX[MAX_STARS], starY[MAX_STARS], starBright[MAX_STARS];
float lineOffset = 0.0f;

void circle(float cx, float cy, float r){  // Sady's Part

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for(int i = 0; i <= 100; i++){
        float a = 2*3.1416f*i/100;
        glVertex2f(cx + r*cosf(a), cy + r*sinf(a));
    }

    glEnd();

}



void halfCircle(float cx, float cy, float r){ // Arnob's Part
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for(int i = 0; i <= 50; i++){
        float a = 3.1416f*i/50;
        glVertex2f(cx + r*cosf(a), cy + r*sinf(a));

    }

    glEnd();

}


// MOVING DASH LINES FUNCTION

void drawMovingLines(float x) // Arnob's Part

{
    glColor3f(1.0f, 1.0f, 1.0f);
    for(float i = -1.2f; i < 1.0f; i += 0.12f){
        float y = i - lineOffset;        // '-' => dashes move DOWN (top to bottom)
        if(y > -1.0f && y < 0.55f){
            glBegin(GL_QUADS);
            glVertex2f(x-0.02f, y);
            glVertex2f(x+0.02f, y);
            glVertex2f(x+0.02f, y+0.06f);

            glVertex2f(x-0.02f, y+0.06f);

            glEnd();

        }

    }
}



void drawRock(float x, float y){  // Arnob's Part
    glBegin(GL_POLYGON);
    glColor3f(0.5f,0.5f,0.5f);
    glVertex2f(x,y);
    glVertex2f(x+0.08f,y+0.02f);
    glVertex2f(x+0.06f,y+0.08f);
    glVertex2f(x-0.02f,y+0.06f);
    glVertex2f(x-0.04f,y+0.02f);
    glEnd();
    glBegin(GL_POLYGON);

    glColor3f(0.3f,0.3f,0.3f);

    glVertex2f(x,y);

    glVertex2f(x+0.04f,y+0.01f);

    glVertex2f(x+0.02f,y+0.04f);

    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.7f,0.7f,0.7f);
    glVertex2f(x+0.02f,y+0.05f);
    glVertex2f(x+0.06f,y+0.07f);
    glVertex2f(x+0.04f,y+0.03f);

    glEnd();

}

void drawCactus(float x, float y){  // Arnob's Part

    glBegin(GL_QUADS);
    glColor3f(0.0f,0.6f,0.25f);

    glVertex2f(x,y);

    glVertex2f(x+0.05f,y);

    glVertex2f(x+0.05f,y+0.25f);

    glVertex2f(x,y+0.25f);

    glEnd();



    glBegin(GL_QUADS);

    glColor3f(0.0f,0.4f,0.15f);

    glVertex2f(x+0.025f,y);

    glVertex2f(x+0.05f,y);

    glVertex2f(x+0.05f,y+0.25f);

    glVertex2f(x+0.025f,y+0.25f);

    glEnd();



    glBegin(GL_QUADS);

    glColor3f(0.0f,0.6f,0.25f);

    glVertex2f(x-0.03f,y+0.12f);

    glVertex2f(x,y+0.12f);

    glVertex2f(x,y+0.17f);

    glVertex2f(x-0.03f,y+0.17f);

    glEnd();



    glBegin(GL_QUADS);

    glColor3f(0.0f,0.6f,0.25f);

    glVertex2f(x+0.05f,y+0.15f);

    glVertex2f(x+0.08f,y+0.15f);

    glVertex2f(x+0.08f,y+0.20f);

    glVertex2f(x+0.05f,y+0.20f);

    glEnd();



    glColor3f(0.0f,0.7f,0.3f);

    halfCircle(x+0.025f,y+0.25f,0.03f);

    glColor3f(0.0f,0.5f,0.2f);

    halfCircle(x+0.03f, y+0.25f,0.02f);

}



//  NEW CITY ENVIRONMENT

void resetCityEnvironment(){
    cityCloudX = -0.8f;
    cityDarkCloudX = -1.4f;
    cityRainY = 0.0f;
    cityBirdX = -1.2f;
    citySideMove = 0.0f;
    citySunAngle = 0.0f;
    cityTimeCount = 0;
    cityRainStart = false;
}

void drawCityCircle(float cx, float cy, float r){
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for(int i = 0; i <= 100; i++){
        float angle = 2.0f * 3.1416f * i / 100.0f;
        float x = r * cosf(angle);
        float y = r * sinf(angle);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

void drawCityWhiteCloud(){
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCityCircle(0.0f, 0.0f, 0.05f);
    drawCityCircle(0.06f, 0.02f, 0.06f);
    drawCityCircle(0.12f, 0.0f, 0.05f);
}

void drawCityDarkCloud(){
    glColor3f(0.18f, 0.18f, 0.20f);
    drawCityCircle(0.0f, 0.0f, 0.07f);
    drawCityCircle(0.08f, 0.02f, 0.08f);
    drawCityCircle(0.16f, 0.0f, 0.07f);
}

void drawCityBird(){
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(3.0f);
    glBegin(GL_LINES);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(-0.04f, 0.04f);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.04f, 0.04f);
    glEnd();
    glLineWidth(1.0f);
}

void drawCityBuilding(float x, float y, float w, float h){
    glColor3f(0.35f, 0.35f, 0.45f);
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + w, y);
        glVertex2f(x + w, y + h);
        glVertex2f(x, y + h);
    glEnd();

    glColor3f(1.0f, 0.9f, 0.2f);
    for(float i = x + 0.01f; i < x + w - 0.01f; i += 0.025f){
        for(float j = y + 0.03f; j < y + h - 0.02f; j += 0.06f){
            glBegin(GL_QUADS);
                glVertex2f(i, j);
                glVertex2f(i + 0.015f, j);
                glVertex2f(i + 0.015f, j + 0.025f);
                glVertex2f(i, j + 0.025f);
            glEnd();
        }
    }
}

void drawCityTree(float x, float y){
    glColor3f(0.45f, 0.22f, 0.08f);
    glBegin(GL_QUADS);
        glVertex2f(x - 0.02f, y);
        glVertex2f(x + 0.02f, y);
        glVertex2f(x + 0.02f, y + 0.12f);
        glVertex2f(x - 0.02f, y + 0.12f);
    glEnd();

    glColor3f(0.0f, 0.5f, 0.1f);
    drawCityCircle(x, y + 0.17f, 0.06f);
    drawCityCircle(x - 0.04f, y + 0.13f, 0.05f);
    drawCityCircle(x + 0.04f, y + 0.13f, 0.05f);
}

void drawCityStreetLight(float x, float y){
    glColor3f(0.05f, 0.05f, 0.05f);
    glBegin(GL_QUADS);
        glVertex2f(x - 0.008f, y);
        glVertex2f(x + 0.008f, y);
        glVertex2f(x + 0.008f, y + 0.22f);
        glVertex2f(x - 0.008f, y + 0.22f);
    glEnd();

    glColor3f(1.0f, 0.95f, 0.3f);
    drawCityCircle(x, y + 0.24f, 0.03f);
}

void drawCityRain(){
    if(!cityRainStart) return;
    glColor3f(0.6f, 0.8f, 1.0f);
    glBegin(GL_LINES);
    for(float x = -1.0f; x <= 1.0f; x += 0.22f){
        for(float y = -1.0f; y <= 1.0f; y += 0.35f){
            float yy = y + cityRainY;
            glVertex2f(x, yy);
            glVertex2f(x + 0.025f, yy - 0.07f);
        }
    }
    glEnd();
}

void drawCitySideObjects(){
    for(int i = 0; i < 4; i++){
        float y = 0.40f - i * 0.55f + citySideMove;

        drawCityBuilding(-0.98f, y, 0.07f, 0.25f);
        drawCityTree(-0.88f, y - 0.05f);
        drawCityStreetLight(-0.83f, y - 0.08f);

        drawCityBuilding(0.91f, y, 0.07f, 0.30f);
        drawCityTree(0.88f, y - 0.05f);
        drawCityStreetLight(0.83f, y - 0.08f);
    }
}

void CityVegetation(){
    drawCitySideObjects();
}

void Road_Environment();

void CityEnvironment(){
    // City sky is matched with the main project sky style
    glBegin(GL_QUADS);
        if(cityRainStart) glColor3f(0.36f, 0.43f, 0.52f);   // rainy but still soft like main sky
        else              glColor3f(0.5f, 0.81f, 0.92f);    // same as main Sky() top color
        glVertex2f(1.0f, 1.0f);
        glVertex2f(-1.0f, 1.0f);

        if(cityRainStart) glColor3f(0.62f, 0.67f, 0.72f);   // rainy bottom sky
        else              glColor3f(1.0f, 1.0f, 1.0f);      // same as main Sky() bottom color
        glVertex2f(-1.0f, 0.20f);
        glVertex2f(1.0f, 0.20f);
    glEnd();

    if(!cityRainStart){
        // Sun with rotating rays, but color/placement kept soft with project sky
        glColor3f(1.0f, 0.82f, 0.0f);
        drawCityCircle(0.72f, 0.74f, 0.08f);

        glColor3f(1.0f, 0.60f, 0.0f);
        glLineWidth(2.0f);
        glPushMatrix();
        glTranslatef(0.72f, 0.74f, 0.0f);
        glRotatef(citySunAngle, 0.0f, 0.0f, 1.0f);
        glBegin(GL_LINES);
        for(int i = 0; i < 12; i++){
            float angle = 2.0f * 3.1416f * i / 12.0f;
            glVertex2f(0.11f * cosf(angle), 0.11f * sinf(angle));
            glVertex2f(0.16f * cosf(angle), 0.16f * sinf(angle));
        }
        glEnd();
        glPopMatrix();
        glLineWidth(1.0f);

        // White clouds from the 1st city file
        glPushMatrix();
        glTranslatef(cityCloudX, 0.78f, 0.0f);
        drawCityWhiteCloud();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(cityCloudX + 0.5f, 0.73f, 0.0f);
        drawCityWhiteCloud();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(cityCloudX - 0.45f, 0.68f, 0.0f);
        drawCityWhiteCloud();
        glPopMatrix();

        // Birds from the 1st city file
        glPushMatrix();
        glTranslatef(cityBirdX, 0.68f, 0.0f);
        drawCityBird();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(cityBirdX + 0.18f, 0.72f, 0.0f);
        drawCityBird();
        glPopMatrix();
    }

    // Dark clouds appear before rain, matched with sky height
    if(cityTimeCount > 250){
        glPushMatrix();
        glTranslatef(cityDarkCloudX, 0.78f, 0.0f);
        drawCityDarkCloud();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(cityDarkCloudX + 0.35f, 0.73f, 0.0f);
        drawCityDarkCloud();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(cityDarkCloudX + 0.70f, 0.79f, 0.0f);
        drawCityDarkCloud();
        glPopMatrix();
    }

    // Road and side ground are drawn by the original project function
    // so the city road looks same as other scenes.
    Road_Environment();

    // City objects and rain features from the 1st file
    drawCitySideObjects();
    drawCityRain();
}


// This old-style cloud function is kept only for village scene, so village remains unchanged.
void drawCircleCity(float cx, float cy, float r){
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for(int i = 0; i <= 100; i++){
        float a = 2.0f * 3.1416f * i / 100.0f;
        glVertex2f(cx + r * cosf(a), cy + r * sinf(a));
    }
    glEnd();
}

void drawCloudCity(float x, float y){
    if(moonY > 0.5f)
        glColor3f(0.0f, 0.0f, 0.15f);
    else
        glColor3f(1.0f, 1.0f, 1.0f);

    drawCircleCity(x, y, 0.05f);
    drawCircleCity(x + 0.05f, y + 0.02f, 0.06f);
    drawCircleCity(x + 0.10f, y, 0.05f);
    drawCircleCity(x + 0.04f, y - 0.02f, 0.045f);
}


void drawHut(float x, float y){

    glColor3f(0.78f,0.66f,0.42f);

    glBegin(GL_QUADS);

    glVertex2f(x,y);

    glVertex2f(x+0.08f,y);

    glVertex2f(x+0.08f,y+0.12f);

    glVertex2f(x,y+0.12f);

    glEnd();



    glColor3f(0.55f,0.37f,0.24f);

    glBegin(GL_TRIANGLES);

    glVertex2f(x-0.01f,y+0.12f);

    glVertex2f(x+0.09f,y+0.12f);

    glVertex2f(x+0.04f,y+0.20f);

    glEnd();



    glColor3f(0.36f,0.20f,0.06f);

    glBegin(GL_QUADS);

    glVertex2f(x+0.025f,y);

    glVertex2f(x+0.055f,y);

    glVertex2f(x+0.055f,y+0.06f);

    glVertex2f(x+0.025f,y+0.06f);

    glEnd();

}



void drawTreeVillage(float x, float y){
    glColor3f(0.42f,0.27f,0.14f);
    glBegin(GL_QUADS);
    glVertex2f(x-0.018f,y);

    glVertex2f(x+0.018f,y);

    glVertex2f(x+0.010f,y+0.10f);

    glVertex2f(x-0.010f,y+0.10f);

    glEnd();



    glColor3f(0.01f,0.01f,0.01f);

    glLineWidth(1.5f);

    glBegin(GL_LINES);

    glVertex2f(x+0.004f,y);

    glVertex2f(x+0.003f,y+0.09f);

    glEnd();



    glColor3f(0.01f,0.01f,0.01f);

    glBegin(GL_TRIANGLES);

    glVertex2f(x,y+0.20f);

    glVertex2f(x-0.09f,y+0.10f);

    glVertex2f(x+0.09f,y+0.10f);

    glEnd();



    glColor3f(0.23f,0.51f,0.13f);

    glBegin(GL_TRIANGLES);

    glVertex2f(x,y+0.26f);

    glVertex2f(x-0.07f,y+0.16f);

    glVertex2f(x+0.07f,y+0.16f);

    glEnd();



    glColor3f(0.31f,0.61f,0.16f);

    glBegin(GL_TRIANGLES);

    glVertex2f(x,y+0.31f);

    glVertex2f(x-0.045f,y+0.22f);

    glVertex2f(x+0.045f,y+0.22f);

    glEnd();

    glColor4f(0.39f,0.78f,0.24f,0.35f);

    circle(x+0.01f,y+0.27f,0.018f);

}



void drawSideObjectsVillage(float offset){
    for(int i=0;i<4;i++){
        float y = 0.38f - i*0.55f + offset;
        drawHut(-0.97f,y+0.04f);
        drawTreeVillage(-0.89f,y-0.05f);
        drawHut( 0.89f,y+0.04f);
        drawTreeVillage( 0.84f,y-0.05f);

    }

}



void Left_Tree(){ // Sady's Part
    glPushMatrix();
    glTranslatef(0.0f,Angle_tree,0);
    glColor3f(0.0f,0.5f,0.2f);
    glBegin(GL_TRIANGLES);
    glVertex2d(-0.8,0.2);
    glVertex2d(-1.0,0.2);
    glVertex2d(-0.9,0.5);
    glEnd();

    glColor3f(0.55f,0.35f,0.18f);
    glBegin(GL_QUADS);
    glVertex2d(-0.85,0.0);
    glVertex2d(-0.95,0.0);
    glVertex2d(-0.95,0.2);
    glVertex2d(-0.85,0.2);
    glEnd();

    glColor3f(0.0f,0.5f,0.2f);
    glBegin(GL_TRIANGLES);
    glVertex2d(-0.8,-0.6);
    glVertex2d(-1.0,-0.6);
    glVertex2d(-0.9,-0.3);
    glEnd();
    glColor3f(0.55f,0.35f,0.18f);

    glBegin(GL_QUADS);

    glVertex2d(-0.85,-0.6);

    glVertex2d(-0.95,-0.6);

    glVertex2d(-0.95,-0.8);

    glVertex2d(-0.85,-0.8);

    glEnd();



    glPopMatrix();

    glPushMatrix();

    glTranslatef(0,Angle_tree,0);

    glColor3f(0.0f,0.5f,0.2f);

    circle(0.9,-0.1,0.05f);

    circle(0.85,-0.2,0.04f);

    circle(0.95,-0.23f,0.04f);

    circle(-0.9,-0.1,0.05f);

    circle(-0.85,-0.2,0.04f);

    circle(-0.95,-0.23f,0.04f);

    glPopMatrix();

}



void Right_Tree(){ //Sady's Part

    glPushMatrix();

    glTranslatef(0.0f,Angle_tree,0);

    glColor3f(0.0f,0.5f,0.2f);
    glBegin(GL_TRIANGLES);
    glVertex2d(0.8,0.2);
    glVertex2d(1,0.2);
    glVertex2d(0.9,0.5);
    glEnd();



    glColor3f(0.55f,0.35f,0.18f);

    glBegin(GL_QUADS);

    glVertex2d(0.85,0.0);

    glVertex2d(0.95,0.0);

    glVertex2d(0.95,0.2);

    glVertex2d(0.85,0.2);

    glEnd();



    glColor3f(0.0f,0.5f,0.2f);

    glBegin(GL_TRIANGLES);

    glVertex2d(0.8,-0.6);

    glVertex2d(1,-0.6);

    glVertex2d(0.9,-0.3);

    glEnd();



    glColor3f(0.55f,0.35f,0.18f);

    glBegin(GL_QUADS);

    glVertex2d(0.85,-0.6);

    glVertex2d(0.95,-0.6);

    glVertex2d(0.95,-0.8);

    glVertex2d(0.85,-0.8);

    glEnd();

    glPopMatrix();

}



//snow orpa

void drawMountain(float x, float y, float w, float h){



    glColor3f(0.15f,0.17f,0.24f);

    glBegin(GL_TRIANGLES);

    glVertex2f(x-w*0.10f,y);

    glVertex2f(x+w*1.10f,y);

    glVertex2f(x+w*0.44f,y+h*0.78f);

    glEnd();



    // mountain body

    glColor3f(0.20f,0.22f,0.30f);

    glBegin(GL_TRIANGLES);

    glVertex2f(x,y);

    glVertex2f(x+w,y);

    glVertex2f(x+w/2,y+h);

    glEnd();



    // Shadow left

    glColor3f(0.10f,0.11f,0.17f);

    glBegin(GL_TRIANGLES);

    glVertex2f(x+w/2,y+h);

    glVertex2f(x,y);

    glVertex2f(x+w*0.40f,y);

    glEnd();



    //lite

    glColor3f(0.25f,0.27f,0.36f);

    glBegin(GL_TRIANGLES);

    glVertex2f(x+w/2,y+h);

    glVertex2f(x+w*0.56f,y);

    glVertex2f(x+w,y);

    glEnd();



    // Snow cap

    glColor3f(0.83f,0.86f,0.93f);

    glBegin(GL_TRIANGLES);

    glVertex2f(x+w*0.33f,y+h*0.62f);

    glVertex2f(x+w*0.67f,y+h*0.62f);

    glVertex2f(x+w/2,y+h);

    glEnd();



    // Snow

    glColor3f(0.58f,0.62f,0.72f);

    glBegin(GL_TRIANGLES);

    glVertex2f(x+w/2,y+h);

    glVertex2f(x+w*0.33f,y+h*0.62f);

    glVertex2f(x+w*0.47f,y+h*0.62f);

    glEnd();





    glColor3f(0.94f,0.96f,0.99f);

    glBegin(GL_TRIANGLES);

    glVertex2f(x+w/2,y+h);

    glVertex2f(x+w*0.53f,y+h*0.63f);

    glVertex2f(x+w*0.62f,y+h*0.70f);

    glEnd();



    glColor3f(0.80f,0.84f,0.91f);

    glBegin(GL_TRIANGLES);

    glVertex2f(x+w*0.33f,y+h*0.62f);

    glVertex2f(x+w*0.41f,y+h*0.62f);

    glVertex2f(x+w*0.37f,y+h*0.55f);

    glVertex2f(x+w*0.59f,y+h*0.62f);

    glVertex2f(x+w*0.67f,y+h*0.62f);

    glVertex2f(x+w*0.63f,y+h*0.55f);

    glEnd();

}

//snow tree

void drawTreeSnow(float x, float y, float s){



    glColor3f(0.30f,0.18f,0.09f);

    glBegin(GL_QUADS);

    glVertex2f(x-0.016f*s,y);

    glVertex2f(x+0.016f*s,y);

    glVertex2f(x+0.012f*s,y+0.08f*s);

    glVertex2f(x-0.012f*s,y+0.08f*s);

    glEnd();

    //bottom dark green

    glColor3f(0.08f,0.26f,0.06f);

    glBegin(GL_TRIANGLES);

    glVertex2f(x-0.088f*s,y+0.080f*s);

    glVertex2f(x+0.088f*s,y+0.080f*s);

    glVertex2f(x,y+0.198f*s);

    glEnd();



    glColor3f(0.88f,0.91f,0.96f);

    glBegin(GL_TRIANGLES);

    glVertex2f(x-0.088f*s,y+0.080f*s);

    glVertex2f(x-0.062f*s,y+0.080f*s);

    glVertex2f(x-0.075f*s,y+0.115f*s);

    glVertex2f(x+0.062f*s,y+0.080f*s);

    glVertex2f(x+0.088f*s,y+0.080f*s);
    glVertex2f(x+0.075f*s,y+0.115f*s);
    glVertex2f(x-0.009f*s,y+0.174f*s);
    glVertex2f(x+0.009f*s,y+0.174f*s);
    glVertex2f(x,y+0.198f*s);

    glEnd();



    // Layer 2

    glColor3f(0.10f,0.31f,0.08f);

    glBegin(GL_TRIANGLES);

    glVertex2f(x-0.070f*s,y+0.145f*s);

    glVertex2f(x+0.070f*s,y+0.145f*s);

    glVertex2f(x,y+0.258f*s);

    glEnd();



    glColor3f(0.89f,0.92f,0.97f);

    glBegin(GL_TRIANGLES);

    glVertex2f(x-0.070f*s,y+0.145f*s);

    glVertex2f(x-0.047f*s,y+0.145f*s);

    glVertex2f(x-0.058f*s,y+0.178f*s);

    glVertex2f(x+0.047f*s,y+0.145f*s);

    glVertex2f(x+0.070f*s,y+0.145f*s);

    glVertex2f(x+0.058f*s,y+0.178f*s);

    glVertex2f(x-0.008f*s,y+0.233f*s);

    glVertex2f(x+0.008f*s,y+0.233f*s);

    glVertex2f(x,y+0.258f*s);

    glEnd();



    // Layer 3

    glColor3f(0.13f,0.38f,0.10f);

    glBegin(GL_TRIANGLES);

    glVertex2f(x-0.050f*s,y+0.205f*s);

    glVertex2f(x+0.050f*s,y+0.205f*s);

    glVertex2f(x,y+0.313f*s);

    glEnd();



    glColor3f(0.90f,0.93f,0.97f);  // snow on L3

    glBegin(GL_TRIANGLES);

    glVertex2f(x-0.050f*s,y+0.205f*s);

    glVertex2f(x-0.032f*s,y+0.205f*s);

    glVertex2f(x-0.041f*s,y+0.236f*s);

    glVertex2f(x+0.032f*s,y+0.205f*s);

    glVertex2f(x+0.050f*s,y+0.205f*s);

    glVertex2f(x+0.041f*s,y+0.236f*s);

    glVertex2f(x-0.006f*s,y+0.288f*s);

    glVertex2f(x+0.006f*s,y+0.288f*s);

    glVertex2f(x,y+0.313f*s);

    glEnd();



    // Layer 4 — top, narrowest, lightest green

    glColor3f(0.17f,0.46f,0.13f);

    glBegin(GL_TRIANGLES);

    glVertex2f(x-0.030f*s,y+0.268f*s);

    glVertex2f(x+0.030f*s,y+0.268f*s);

    glVertex2f(x,y+0.370f*s);

    glEnd();



    glColor3f(0.92f,0.95f,0.98f);  // heavy snow cap on top layer

    glBegin(GL_TRIANGLES);

    glVertex2f(x-0.030f*s,y+0.268f*s);

    glVertex2f(x-0.009f*s,y+0.268f*s);

    glVertex2f(x-0.019f*s,y+0.296f*s);

    glVertex2f(x+0.009f*s,y+0.268f*s);

    glVertex2f(x+0.030f*s,y+0.268f*s);

    glVertex2f(x+0.019f*s,y+0.296f*s);

    glVertex2f(x-0.007f*s,y+0.342f*s);

    glVertex2f(x+0.007f*s,y+0.342f*s);

    glVertex2f(x,y+0.370f*s);

    glEnd();

}



//lamp

void drawLampPost(float x, float y, int mir){

    float m = mir ? -1.0f : 1.0f;

    // Base plate

    glColor3f(0.44f,0.45f,0.52f);

    glBegin(GL_QUADS);

    glVertex2f(x-0.018f,y);

    glVertex2f(x+0.018f,y);

    glVertex2f(x+0.014f,y+0.016f);

    glVertex2f(x-0.014f,y+0.016f);

    glEnd();



    // Main pole

    glColor3f(0.50f,0.51f,0.58f);

    glBegin(GL_QUADS);

    glVertex2f(x-0.010f,y+0.016f);

    glVertex2f(x+0.010f,y+0.016f);

    glVertex2f(x+0.007f,y+0.280f);

    glVertex2f(x-0.007f,y+0.280f);

    glEnd();



    // Highlight stripe

    glColor3f(0.70f,0.71f,0.78f);

    glBegin(GL_QUADS);

    glVertex2f(x+0.002f,y+0.016f);

    glVertex2f(x+0.005f,y+0.016f);

    glVertex2f(x+0.004f,y+0.280f);

    glVertex2f(x+0.001f,y+0.280f);

    glEnd();



    // Arm horizontal

    glColor3f(0.50f,0.51f,0.58f);

    glBegin(GL_QUADS);

    glVertex2f(x-0.005f,y+0.270f);

    glVertex2f(x+m*0.012f,y+0.270f);

    glVertex2f(x+m*0.012f,y+0.292f);

    glVertex2f(x-0.005f,   y+0.292f);

    glEnd();



    glBegin(GL_QUADS);

    glVertex2f(x+m*0.010f,y+0.268f);

    glVertex2f(x+m*0.075f,y+0.268f);

    glVertex2f(x+m*0.075f,y+0.282f);

    glVertex2f(x+m*0.010f,y+0.282f);

    glEnd();



    // Lamp shade

    glColor3f(0.48f,0.43f,0.09f);

    glBegin(GL_QUADS);

    glVertex2f(x+m*0.053f,y+0.258f);

    glVertex2f(x+m*0.097f,y+0.258f);

    glVertex2f(x+m*0.093f,y+0.288f);

    glVertex2f(x+m*0.057f,y+0.288f);

    glEnd();



    glColor3f(0.34f,0.30f,0.06f);

    glBegin(GL_QUADS);

    glVertex2f(x+m*0.050f,y+0.288f);

    glVertex2f(x+m*0.100f,y+0.288f);

    glVertex2f(x+m*0.100f,y+0.297f);

    glVertex2f(x+m*0.050f,y+0.297f);

    glEnd();





    if(moonY > 0.5f){

        glEnable(GL_BLEND);

        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

        glColor4f(1.0f,0.88f,0.38f,0.10f);

        circle(x+m*0.075f,y+0.272f,0.042f);

        glColor4f(1.0f,0.91f,0.48f,0.18f);

        circle(x+m*0.075f,y+0.272f,0.028f);

        glDisable(GL_BLEND);

        glColor3f(1.0f,0.96f,0.72f);

        circle(x+m*0.075f,y+0.272f,0.016f);

        glColor3f(1.0f,1.00f,0.90f);

        circle(x+m*0.075f,y+0.272f,0.007f);



        // Light cone projected onto ground

        glEnable(GL_BLEND);

        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

        glBegin(GL_TRIANGLES);

        glColor4f(1.0f,0.93f,0.55f,0.18f);

        glVertex2f(x+m*0.075f, y+0.272f);

        glColor4f(1.0f,0.93f,0.55f,0.00f);

        glVertex2f(x+m*0.075f+0.09f, y+0.272f-0.24f);

        glVertex2f(x+m*0.075f-0.09f, y+0.272f-0.24f);

        glEnd();

        glDisable(GL_BLEND);



    } else {

        //lamp off day time

        glColor3f(0.35f,0.33f,0.28f);

        circle(x+m*0.075f,y+0.272f,0.010f);

    }

    // Snow

    glColor3f(0.88f,0.91f,0.96f);

    glBegin(GL_TRIANGLES);

    glVertex2f(x+m*0.050f,y+0.297f);

    glVertex2f(x+m*0.100f,y+0.297f);

    glVertex2f(x+m*0.075f,y+0.312f);

    glEnd();



    glColor3f(0.95f,0.97f,1.00f);

    glBegin(GL_TRIANGLES);

    glVertex2f(x+m*0.063f,y+0.297f);

    glVertex2f(x+m*0.085f,y+0.297f);

    glVertex2f(x+m*0.075f,y+0.309f);

    glEnd();

}



void drawSnow(){



    glPointSize(1.5f);

    glBegin(GL_POINTS);

    glColor3f(0.82f,0.86f,0.94f);

    for(int i=0;i<MAX_SNOW/3;i++) glVertex2f(snowX[i],snowY_arr[i]);

    glEnd();



    glPointSize(2.5f);

    glBegin(GL_POINTS);

    glColor3f(0.93f,0.95f,0.98f);

    for(int i=MAX_SNOW/3;i<(MAX_SNOW*2)/3;i++) glVertex2f(snowX[i],snowY_arr[i]);

    glEnd();



    // Front layer

    glPointSize(4.0f);

    glBegin(GL_POINTS);

    glColor3f(1.0f,1.0f,1.0f);

    for(int i=(MAX_SNOW*2)/3;i<MAX_SNOW;i++) glVertex2f(snowX[i],snowY_arr[i]);

    glEnd();

    glPointSize(1.0f);

}



//snow

void initSnowNight(){

    srand((unsigned)time(NULL));

    for(int i=0;i<MAX_STARS;i++){

        starX[i] = -1.0f + (float)rand()/RAND_MAX*2.0f;

        starY[i] = 0.62f + (float)rand()/RAND_MAX*0.36f;

        starBright[i] = 0.40f + (float)rand()/RAND_MAX*0.60f;

    }

    for(int i=0;i<MAX_SNOW;i++){

        snowX[i] = -1.0f + (float)rand()/RAND_MAX*2.0f;

        snowY_arr[i] = -1.0f + (float)rand()/RAND_MAX*2.0f;

        snowDriftX[i] = -0.0006f + (float)rand()/RAND_MAX*0.0012f;

        if

            (i < MAX_SNOW/3)snowSpeed[i] = 0.002f + (float)rand()/RAND_MAX*0.002f;

        else if

            (i < (MAX_SNOW*2)/3) snowSpeed[i] = 0.004f + (float)rand()/RAND_MAX*0.003f;

        else

            snowSpeed[i] = 0.006f + (float)rand()/RAND_MAX*0.004f;

    }

}



void SnowSky(){



    if(moonY <= 0.5f){

        glBegin(GL_QUADS);

        glColor3f(0.56f,0.78f,0.90f); glVertex2d( 1, 1);

        glColor3f(0.56f,0.78f,0.90f); glVertex2d(-1, 1);

        glColor3f(0.82f,0.92f,0.97f); glVertex2d(-1, 0.20f);

        glColor3f(0.82f,0.92f,0.97f); glVertex2d( 1, 0.20f);

        glEnd();



        glColor3f(1.0f,0.92f,0.60f);

        circle(-sunY*0.4f, sunY, 0.10f);



        glEnable(GL_BLEND);

        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

        glColor4f(1.0f,0.96f,0.70f,0.12f);

        circle(-sunY*0.4f,sunY,0.20f);

        glColor4f(1.0f,0.96f,0.70f,0.06f);

        circle(-sunY*0.4f,sunY,0.30f);

        glDisable(GL_BLEND);



        glEnable(GL_BLEND);

        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

        glBegin(GL_QUADS);

        glColor4f(0.90f,0.95f,0.98f,0.55f);

        glVertex2f(-1,0.55f);

        glVertex2f(1,0.55f);

        glColor4f(0.90f,0.95f,0.98f,0.00f);

        glVertex2f(1,0.78f);

        glVertex2f(-1,0.78f);

        glEnd();

        glDisable(GL_BLEND);





        glPushMatrix();

        glTranslatef(Angle,0,0);

        glColor3f(0.97f,0.97f,1.00f);

        circle(-0.70f,0.74f,0.11f);

        circle(-0.80f,0.74f,0.09f);

        circle(-0.60f,0.74f,0.08f);

        circle(-0.75f,0.78f,0.07f);

        circle(-0.65f,0.77f,0.06f);

        circle( 0.30f,0.72f,0.11f);

        circle( 0.40f,0.72f,0.09f);

        circle( 0.20f,0.72f,0.08f);

        circle( 0.35f,0.76f,0.07f);

        circle( 0.25f,0.75f,0.06f);

        glPopMatrix();





        glPushMatrix();

        glTranslatef(Angle*0.6f,0,0);

        glColor3f(0.94f,0.95f,0.99f);

        circle(-0.20f,0.80f,0.09f);

        circle(-0.10f,0.80f,0.08f);

        circle(-0.30f,0.79f,0.07f);

        circle( 0.70f,0.77f,0.09f);

        circle( 0.80f,0.77f,0.07f);

        circle( 0.62f,0.76f,0.07f);

        glPopMatrix();



    } else {



        glBegin(GL_QUADS);

        glColor3f(0.00f,0.00f,0.04f);

        glVertex2d( 1, 1);

        glVertex2d(-1, 1);

        glColor3f(0.01f,0.02f,0.08f);

        glVertex2d(-1, 0.62f);

        glVertex2d(1, 0.62f);

        glEnd();



        glBegin(GL_QUADS);

        glColor3f(0.01f,0.02f,0.08f);

        glVertex2d( 1, 0.62f);

        glVertex2d(-1, 0.62f);

        glColor3f(0.03f,0.05f,0.16f);

        glVertex2d(-1, 0.20f);

        glVertex2d(1, 0.20f);

        glEnd();



        //star

        glPointSize(1.0f);

        glBegin(GL_POINTS);

        for(int i=0;i<MAX_STARS/3;i++){

            float b=starBright[i]*(0.50f+0.50f*sinf(cloudAnim*2.8f+i*1.31f));

            glColor3f(b*0.82f,b*0.87f,b);

            glVertex2f(starX[i],starY[i]);

        }

        glEnd();

        glPointSize(2.0f);

        glBegin(GL_POINTS);

        for(int i=MAX_STARS/3;i<(MAX_STARS*2)/3;i++){

            float b=starBright[i]*(0.60f+0.40f*sinf(cloudAnim*3.6f+i*0.97f));

            glColor3f(b,b,b*0.92f);

            glVertex2f(starX[i],starY[i]);

        }

        glEnd();

        glPointSize(3.0f);

        glBegin(GL_POINTS);

        for(int i=(MAX_STARS*2)/3;

        i<MAX_STARS;i++){

            float b=starBright[i]*(0.70f+0.30f*sinf(cloudAnim*4.3f+i*0.77f));

            glColor3f(b,b*0.96f,b*0.86f);

            glVertex2f(starX[i],starY[i]);

        }

        glEnd();

        glPointSize(1.0f);



        //moon

        glEnable(GL_BLEND);

        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

        glColor4f(0.84f,0.87f,0.95f,0.05f);

        circle(0.68f,0.82f,0.20f);

        glColor4f(0.87f,0.90f,0.96f,0.10f);

        circle(0.68f,0.82f,0.15f);

        glColor4f(0.90f,0.93f,0.98f,0.18f);

        circle(0.68f,0.82f,0.12f);

        glDisable(GL_BLEND);



        glColor3f(0.96f,0.97f,1.00f);

        circle(0.68f,0.82f,0.090f);

        glColor3f(0.88f,0.89f,0.93f);

        circle(0.73f,0.86f,0.023f);

        glColor3f(0.91f,0.92f,0.95f);

        circle(0.63f,0.80f,0.016f);

        glColor3f(0.02f,0.03f,0.09f);

        circle(0.73f,0.84f,0.074f);





        glPushMatrix();

        glTranslatef(Angle,0,0);

        glColor3f(0.09f,0.10f,0.18f);

        circle(-0.68f,0.800f,0.086f);

        circle(-0.60f,0.812f,0.072f);

        circle(-0.78f,0.792f,0.068f);

        circle(-0.52f,0.796f,0.060f);

        circle( 0.22f,0.820f,0.078f);

        circle( 0.30f,0.830f,0.066f);

        circle( 0.13f,0.814f,0.062f);



        glColor3f(0.05f,0.06f,0.12f);

        circle(-0.75f,0.774f,0.098f);

        circle(-0.65f,0.784f,0.083f);

        circle(-0.84f,0.764f,0.078f);

        circle( 0.25f,0.804f,0.088f);

        circle( 0.35f,0.814f,0.078f);

        circle( 0.15f,0.794f,0.072f);

        glPopMatrix();







        glEnable(GL_BLEND);

        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

        glColor4f(0.0f,0.0f,0.1f,0.50f);

        glBegin(GL_QUADS);

        glVertex2f(-1,-1);

        glVertex2f(1,-1);

        glVertex2f(1,1);

        glVertex2f(-1,1);

        glEnd();

        glDisable(GL_BLEND);

    }

}



void SnowVegetation(){

    glPushMatrix();

    glTranslatef(0.0f, Angle_tree, 0.0f);



    /* LEFT SIDE */

    drawMountain(-0.99f,  0.370f, 0.170f, 0.215f);

    drawTreeSnow (-0.940f, 0.305f, 0.60f);

    drawTreeSnow (-0.880f, 0.295f, 0.45f);

    drawLampPost (-0.840f, 0.100f, 0);



    drawMountain(-0.99f, -0.185f, 0.170f, 0.215f);

    drawTreeSnow (-0.940f,-0.250f, 0.60f);

    drawTreeSnow (-0.880f,-0.260f, 0.45f);

    drawLampPost (-0.840f,-0.455f, 0);



    drawMountain(-0.99f, -0.740f, 0.170f, 0.215f);

    drawTreeSnow (-0.940f,-0.805f, 0.60f);

    drawTreeSnow (-0.880f,-0.815f, 0.45f);

    drawLampPost (-0.840f,-1.010f, 0);



    drawMountain(-0.99f, -1.295f, 0.170f, 0.215f);

    drawTreeSnow (-0.940f,-1.360f, 0.60f);

    drawTreeSnow (-0.880f,-1.370f, 0.45f);



    /* RIGHT SIDE (mirror) */

    drawMountain( 0.820f,  0.370f, 0.170f, 0.215f);

    drawTreeSnow ( 0.880f,  0.305f, 0.60f);

    drawTreeSnow ( 0.935f,  0.295f, 0.45f);

    drawLampPost ( 0.840f,  0.100f, 1);



    drawMountain( 0.820f, -0.185f, 0.170f, 0.215f);

    drawTreeSnow ( 0.880f, -0.250f, 0.60f);

    drawTreeSnow ( 0.935f, -0.260f, 0.45f);

    drawLampPost ( 0.840f, -0.455f, 1);



    drawMountain( 0.820f, -0.740f, 0.170f, 0.215f);

    drawTreeSnow ( 0.880f, -0.805f, 0.60f);

    drawTreeSnow ( 0.935f, -0.815f, 0.45f);

    drawLampPost ( 0.840f, -1.010f, 1);



    drawMountain( 0.820f, -1.295f, 0.170f, 0.215f);

    drawTreeSnow ( 0.880f, -1.360f, 0.60f);

    drawTreeSnow ( 0.935f, -1.370f, 0.45f);



    glPopMatrix();

}



void drawRoadCenterLine(){  // Arnob's Part

    glColor3f(0.86f,0.75f,0.0f);

    glBegin(GL_QUADS);

    glVertex2f(-0.024f,-1);

    glVertex2f(-0.007f,-1);

    glVertex2f(-0.007f,0.55f);

    glVertex2f(-0.024f,0.55f);

    glEnd();

    glBegin(GL_QUADS);

    glVertex2f(0.007f,-1);

    glVertex2f(0.024f,-1);

    glVertex2f(0.024f,0.55f); glVertex2f(0.007f,0.55f);

    glEnd();



}

//arnob er part

void Road_Environment(){



    if (sceneType==0)

        glColor3f(0.0f,0.6f,0.2f);

    else if (sceneType==1)

        glColor3f(0.9f,0.75f,0.4f);

    else if (sceneType==4)

        glColor3f(1.0f,1.0f,1.0f);

    else

        glColor3f(0.55f,0.45f,0.3f);



    glBegin(GL_QUADS);  // Left side

    glVertex2f(0.82f,-1);

    glVertex2f(1.0f,-1);

    glVertex2f(1.0f,0.55f);

    glVertex2f(0.82f,0.55f);

    glEnd();



    glBegin(GL_QUADS);  // Right side

    glVertex2f(-0.82f,-1);

    glVertex2f(-1.0f,-1);

    glVertex2f(-1.0f,0.55f);

    glVertex2f(-0.82f,0.55f);

    glEnd();



    glBegin(GL_QUADS);  // Road surface

    glColor3f(0.11f,0.12f,0.15f);

    glVertex2f(-0.82f,-1);

    glVertex2f(0.82f,-1.0f);

    glVertex2f(0.82f,0.55f);

    glVertex2f(-0.82f,0.55f);

    glEnd();



    glLineWidth(2.0f);

    glBegin(GL_LINES);  // Lane edge lines

    glColor3f(0.85f,0.85f,0.85f);

    glVertex2d(-0.6f,-1);

    glVertex2d(-0.6f,0.55);

    glVertex2d( 0.6f,-1);

    glVertex2d( 0.6f,0.55);

    glEnd();



    drawRoadCenterLine();

    drawMovingLines(-0.35f);

    drawMovingLines( 0.35f);

    glLineWidth(1.0f);

}



void drawText(const char* text, float x, float y){ //Sady's part

    glRasterPos2f(x,y);

    for(int i=0;text[i]!='\0';i++) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,text[i]);

}



void moon(){  // Sady's Part

    glColor3f(0.98f,0.96f,0.98f);

    circle(moonY*0.4f,moonY,0.1f);

}



void enemy_car(){  // Arnob's Part

    glPushMatrix(); glTranslatef(enemy_x,enemy_y,0);

    glColor3f(1.0f,1.0f,0.0f);

    glBegin(GL_QUADS);

    glVertex2d(-0.1,-0.9);

    glVertex2d(0.1,-0.9);

    glVertex2d(0.1,-0.6);

    glVertex2d(-0.1,-0.6);

    glEnd();



    glColor3f(0.0f,0.0f,0.0f);

    glBegin(GL_QUADS);

    glVertex2d(-0.08,-0.7);

    glVertex2d(0.08,-0.7);

    glVertex2d(0.08,-0.62);

    glVertex2d(-0.08,-0.62);

    glEnd();



    glBegin(GL_QUADS);

    glVertex2d(-0.08,-0.88);

    glVertex2d(0.08,-0.88);

    glVertex2d(0.08,-0.82);

    glVertex2d(-0.08,-0.82);

    glEnd();



    glPointSize(5.0f);

    glColor3f(1,1,1);

    glBegin(GL_POINTS);

    glVertex2d(-0.06,-0.61);

    glVertex2d(0.06,-0.61);

    glEnd();



    glColor3f(0,0,0);

    glBegin(GL_QUADS);

    glVertex2d(-0.12,-0.7);

    glVertex2d(-0.1,-0.7);

    glVertex2d(-0.1,-0.65);

    glVertex2d(-0.12,-0.65);

    glVertex2d(0.1,-0.7);

    glVertex2d(0.12,-0.7);

    glVertex2d(0.12,-0.65);

    glVertex2d(0.1,-0.65);

    glVertex2d(-0.12,-0.85);

    glVertex2d(-0.1,-0.85);

    glVertex2d(-0.1,-0.8);

    glVertex2d(-0.12,-0.8);

    glVertex2d(0.1,-0.85);

    glVertex2d(0.12,-0.85);

    glVertex2d(0.12,-0.8);

    glVertex2d(0.1,-0.8);

    glEnd();

    glPopMatrix();

}



void Player_car(){ // Sady's Part

    glColor3f(0.0f,0.0f,1.0f);

    glBegin(GL_QUADS);

    glVertex2d(-0.1,-0.9);

    glVertex2d(0.1,-0.9);

    glVertex2d(0.1,-0.6);

    glVertex2d(-0.1,-0.6);

    glEnd();



    glColor3f(0,0,0);

    glBegin(GL_QUADS);

    glVertex2d(-0.08,-0.7);

    glVertex2d(0.08,-0.7);

    glVertex2d(0.08,-0.62);

    glVertex2d(-0.08,-0.62);

    glEnd();



    glBegin(GL_QUADS);

    glVertex2d(-0.08,-0.88);

    glVertex2d(0.08,-0.88);

    glVertex2d(0.08,-0.82);

    glVertex2d(-0.08,-0.82);

    glEnd();



    glPointSize(5.0f);

    glColor3f(1,1,1);

    glBegin(GL_POINTS);

    glVertex2d(-0.06,-0.61);

    glVertex2d(0.06,-0.61);

    glEnd();



    glColor3f(0,0,0);

    glBegin(GL_QUADS);

    glVertex2d(-0.12,-0.7);

    glVertex2d(-0.1,-0.7);

    glVertex2d(-0.1,-0.65);

    glVertex2d(-0.12,-0.65);

    glVertex2d(0.1,-0.7);

    glVertex2d(0.12,-0.7);

    glVertex2d(0.12,-0.65);

    glVertex2d(0.1,-0.65);

    glVertex2d(-0.12,-0.85);

    glVertex2d(-0.1,-0.85);

    glVertex2d(-0.1,-0.8);

    glVertex2d(-0.12,-0.8);

    glVertex2d(0.1,-0.85);

    glVertex2d(0.12,-0.85);

    glVertex2d(0.12,-0.8);

    glVertex2d(0.1,-0.8);

    glEnd();

}



void cloud(){ //Sady's Part

    glPushMatrix();

    if(moonY<=0.5f) glColor3f(1,1,1);

    else

        glColor3f(0,0,0.2f);

    glTranslatef(Angle,0,0);

    circle(-0.7f,0.65f,0.11f);

    circle(-0.8f,0.65f,0.09f);

    circle(-0.6f,0.65f,0.08f);

    circle( 0.3f,0.65f,0.11f);

    circle( 0.4f,0.65f,0.09f);

    circle( 0.2f,0.65f,0.08f);

    glPopMatrix();

}



void Sky(){ // Sady's Part

    glBegin(GL_QUADS);

    glColor3f(0.5f,0.81f,0.92f);

    glVertex2d(1,1);

    glVertex2d(-1,1);

    glColor3f(1.0f,1.0f,1.0f);

    glVertex2d(-1,0.2);

    glVertex2d(1,0.2);

    glEnd();

}



void Sun(){ //Sady's Part

    glColor3f(1.0f,0.8f,0.0f);

    circle(-sunY*0.4f,sunY,0.1f);

}



void DesertVegetation(){  // Arnob's Part

    glPushMatrix();
    glTranslatef(0.0f,Angle_tree,0);
    drawRock(0.85f,-0.6f);
    drawRock(0.9f,-0.8f);
    drawRock(-0.95f,-0.7f);
    drawRock(-0.9f,-0.9f);

    drawCactus(0.9f,0.1f); drawCactus(-0.95f,0.1f);

    glPopMatrix();

}



// CityVegetation is defined in the new city environment section

void VillageVegetation()
{ drawSideObjectsVillage(sideMove); }



void update(int value){ //Sady's Part

    float playerLeft  = car - 0.12f;

    float playerRight = car + 0.12f;

    float playerTop=-0.6f, playerBottom=-0.9f;

    float enemyLeft=enemy_x-0.12f, enemyRight=enemy_x+0.12f;

    float enemyTop=enemy_y-0.6f,   enemyBottom=enemy_y-0.9f;



    if(isGameOver || !gameStarted) return;



    Angle += speed_cloud;

    if(Angle > 1.5f) Angle = -1.5f;



    Angle_tree -= speed_Tree;

    if(Angle_tree < -1.6f) Angle_tree = 0.08f;



    Angle_rock -= speed_rock;

    if(Angle_rock < -1.0f) Angle_rock = 0.01f;



    // Update only the new city environment when city scene is active
    if(sceneType == 2){
        cityTimeCount++;

        cityCloudX += 0.003f;
        if(cityCloudX > 1.2f) cityCloudX = -1.2f;

        cityBirdX += 0.003f;
        if(cityBirdX > 1.2f) cityBirdX = -1.2f;

        citySideMove -= 0.003f;
        if(citySideMove < -0.55f) citySideMove = 0.0f;

        citySunAngle += 0.2f;
        if(citySunAngle > 360.0f) citySunAngle = 0.0f;

        if(cityTimeCount > 250){
            cityDarkCloudX += 0.003f;
            cityRainStart = true;
        }

        cityRainY -= 0.012f;
        if(cityRainY < -0.35f) cityRainY = 0.0f;
    }

    cloudX += 0.003f;

    if(cloudX > 1.2f) cloudX = -1.2f;

    sideMove -= 0.003f;

    if(sideMove < -0.55f) sideMove = 0.0f;

    cloudAnim += 0.003f;

    if(cloudAnim > 2.0f) cloudAnim = -2.0f;

    treeAnim += 0.01f;

    if(treeAnim > 1.5f) treeAnim = 0.0f;

    lineOffset += 0.02f;

    if(lineOffset > 0.12f) lineOffset = 0.0f;

    // Snow particles fall downward with gentle sideways drift

    for(int i=0;i<MAX_SNOW;i++){

        snowY_arr[i] -= snowSpeed[i];

        snowX[i]     += snowDriftX[i];

        if(snowY_arr[i] < -1.0f){

            snowY_arr[i] = 1.0f;

            snowX[i]     = -1.0f + (float)rand()/RAND_MAX*2.0f;

        }

        if(snowX[i] < -1.05f || snowX[i] > 1.05f)

            snowDriftX[i] = -snowDriftX[i];

    }



    sunY  -= speed_sun_moon; if(sunY  < -1.5f) sunY  = 1.5f;

    moonY += speed_sun_moon; if(moonY >  1.5f) moonY = -1.5f;



    enemy_y -= enemy_speed;

    if(playerRight>=enemyLeft && playerLeft<=enemyRight &&

       playerTop>=enemyBottom && playerBottom<=enemyTop)

        isGameOver = 1;



    if(enemy_y < -1.5f){

        enemy_y = 1.2f; score++;

        int r = rand()%3;

        enemy_x = (r==0)?-0.4f:(r==1)?0.0f:0.4f;

        if(score>= 3&&score<=10) enemy_speed+=0.001f;

        if(score>=11&&score<=20) enemy_speed+=0.001f;

        if(score>=21&&score<=30) enemy_speed+=0.001f;

        if(score>=30&&score<=40) enemy_speed+=0.001f;

    }



    // Scene time update  // Arnob's Part

    sceneTimer += 0.016f;

    if(sceneTimer >= desertTimer){
        sceneType = (sceneType+1)%5;
        sceneTimer = 0.0f; desertTimer = 15.0f;
        if(sceneType == 2) resetCityEnvironment();
    }



    glutPostRedisplay();

    glutTimerFunc(16,update,0);

}



void display(){  // Arnob's Part

    glClear(GL_COLOR_BUFFER_BIT);
    if(sceneType == 2){
        CityEnvironment();

    } else if(sceneType != 4){
        Sky(); Sun(); moon(); cloud();

        Road_Environment();

    } else {
        SnowSky();
        Road_Environment();
    }

    if(sceneType!=4 || moonY<=0.5f){
        glBegin(GL_QUADS);
        glColor3f(0,0,0);
        glVertex2f(-1,0.9f); glVertex2f(1,0.9f); glVertex2f(1,1); glVertex2f(-1,1);

        glEnd();

    }



    // Vegetation — same call pattern for all scenes

    if  (sceneType==0){ Left_Tree(); Right_Tree(); }

    else if (sceneType==1){ DesertVegetation(); }

    else if (sceneType==2){
        // City environment is already fully drawn by CityEnvironment()
    }

    else if (sceneType==3){ VillageVegetation();

    drawCloudCity(cloudX,0.84f);

    drawCloudCity(cloudX-0.45f,0.78f); }

    else if (sceneType==4){ SnowVegetation(); drawSnow(); }



    // Night

    if(moonY>0.5f && sceneType!=4){

        glEnable(GL_BLEND);

        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

        glColor4f(0,0,0.1f,0.6f);

        glBegin(GL_QUADS);

        glVertex2f(-1,-1);

        glVertex2f(1,-1);

        glVertex2f(1,1);

        glVertex2f(-1,1);

        glEnd();

        glDisable(GL_BLEND);

    }



    // Cars

    glPushMatrix(); glTranslatef(car,0,0); Player_car(); glPopMatrix();

    enemy_car();



    // HUD

    char scoreStr[20]; sprintf(scoreStr,"Score: %d",(int)score);

    glColor3f(1,1,1); drawText(scoreStr,-0.1f,0.93f);



    if      (sceneType==0){ glColor3f(0,1,0);

    drawText("GREEN FIELD",-0.22f,0.85f); }



    else if (sceneType==1){glColor3f(1,0.8f,0);

    drawText("DESERT AREA",-0.2f, 0.85f); }



    else if (sceneType==2){ glColor3f(0.5f,0.7f,1);

    drawText("CITY AREA",-0.18f,0.85f); }

    else if (sceneType==3){ glColor3f(0.2f,0.8f,0.2f);

    drawText("VILLAGE AREA",-0.2f,0.85f); }

    else                  { glColor3f(0.7f,0.8f,1);

    drawText("SNOW NIGHT", -0.18f,0.85f); }



    if(!gameStarted){ glColor3f(1,0,0); drawText("Press 'Space' to start",-0.25f,-0.3f); }

    if(isGameOver){

        glColor3f(1,1,0.6f);

        drawText("GAME OVER!",-0.1f,0.0f);

        drawText("Press 'r' to Restart",-0.3f,-0.1f);

    }

    glutSwapBuffers();

}



void keyboard(unsigned char key, int x, int y){ //Sady's Part

    if(isGameOver && key!='r' && key!=' ') return;

    switch(key){

        case 'a': if(car>-0.65f&&gameStarted&&!isGameOver) car-=0.1f; break;

        case 'd': if(car< 0.65f&&gameStarted&&!isGameOver) car+=0.1f; break;

        case ' ':

            if(!gameStarted||isGameOver){

                gameStarted=1;
                isGameOver=0;
                score=0;
                enemy_y=1.0f;
                car=0.0f;

                sceneType=0;sceneTimer=0.0f;desertTimer=15.0f;
                resetCityEnvironment();

                glutTimerFunc(16,update,0);

            }

            break;

        case 'r':

            isGameOver=0;
            gameStarted=1;
            score=0;
            enemy_y=1.2f;
            car=0.0f;
            sceneType=0;sceneTimer=0.0f;desertTimer=15.0f;
            resetCityEnvironment();

            glutTimerFunc(16,update,0);

            break;

        case 27: exit(0);

    }

    glutPostRedisplay();

}



int main(int argc, char **argv){

    srand(time(0));

    glutInit(&argc,argv);

    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);

    glutInitWindowSize(1000,700);

    glutCreateWindow("Final Scene - Green Field, Desert, City, Village & Snow Night");

    glClearColor(0.01f,0.01f,0.05f,1.0f);

    initSnowNight();

    glutKeyboardFunc(keyboard);

    glutDisplayFunc(display);

    glutTimerFunc(16,update,0);

    glutMainLoop();

    return 0;

}
