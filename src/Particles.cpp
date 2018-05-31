#include "include/Particles.hpp"


void Particles::prepareRender()
{
  particleEffect.enableProgram();
  GLuint color = glGetUniformLocation(particleEffect.getProgram(), "color");
  glUniform1i(color, 0);
  glShadeModel(GL_SMOOTH);				// Enable Smooth Shading
  glClearColor(0.0f,0.0f,0.0f,0.0f);	// Black Background
  glClearDepth(1.0f);					// Depth Buffer Setup
  glDisable(GL_DEPTH_TEST);				// Disable Depth Testing
  glEnable(GL_BLEND);					// Enable Blending
  glBlendFunc(GL_SRC_ALPHA,GL_ONE);		// Type Of Blending To Perform
  glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
  glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);			// Really Nice Point Smoothing
  glActiveTexture(GL_TEXTURE0 + 0);
  glEnable(GL_TEXTURE_2D);				// Enable Texture Mapping
  glBindTexture(GL_TEXTURE_2D,partTex);	// Select Our Texture
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  fadeEffect = glGetUniformLocation(particleEffect.getProgram(), "fade");

  //std::cout << "PrepareRender" << std::endl;

}

void Particles::disableRender()
{
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);
  particleEffect.disableProgram();
}

Particles::Particles(glm::mat4 &matrixToExplodingObject)
{
  //auto mat = matrixToExplodingObject;
  //matrix_[3] = matrixToExplodingObject[3];
  //std::cout << "matrix z: " << matrix[3].z << std::endl;
  //matrix_ = glm::translate(glm::mat4(), glm::vec3(matrixToExplodingObject[3]));
  this->privateInit();
}

//Particles::~Particles()
//{

//}

void Particles::privateUpdate() {}
void Particles::privateInit()
{
  particleEffect.loadShaders("shaders/part.vert", "shaders/part.frag");
  /* load an image file directly as a new OpenGL texture */
  partTex = SOIL_load_OGL_texture(
      (_texturepath + "particle.bmp").c_str(),
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

  if (0 == partTex) {
    printf("SOIL loading error: '%s'\n", SOIL_last_result());
  }


  for (loop=0;loop<MAX_PARTICLES;loop++)			// Initials All The Textures
  {
    particle[loop].active=true;				// Make All The Particles Active
    particle[loop].life=1.0f;				// Give All The Particles Full Life
    particle[loop].fade=float(rand()%100)/1000.0f+0.003f;	// Random Fade Speed
    particle[loop].r=colors[loop*(12/MAX_PARTICLES)][0];	// Select Red Rainbow Color
    particle[loop].g=colors[loop*(12/MAX_PARTICLES)][1];	// Select Red Rainbow Color
    particle[loop].b=colors[loop*(12/MAX_PARTICLES)][2];	// Select Red Rainbow Color
    particle[loop].xi=float((rand()%50)-26.0f)*100.0f;	// Random Speed On X Axis
    particle[loop].yi=float((rand()%50)-25.0f)*100.0f;	// Random Speed On Y Axis
    particle[loop].zi=float((rand()%50)-25.0f)*100.0f;	// Random Speed On Z Axis
    particle[loop].xg=0.0f;					// Set Horizontal Pull To Zero
    particle[loop].yg=-0.8f;				// Set Vertical Pull Downward
    particle[loop].zg=0.0f;					// Set Pull On Z Axis To Zero
    particle[loop].x = matrix_[3].x; //Initialize X position
    particle[loop].y = matrix_[3].y; //Initialize Y position
    particle[loop].z = matrix_[3].z; //Initialize Z position
  }

  //std::cout << "Particle[0] X: " << particle[999].x << "Y: " << particle[0].y << " Z: " << matrix_[3].z << std::endl;
}

void Particles::privateRender() {
  //std::cout << "Render" << std::endl;
  bool faded = false;
  prepareRender();



  for (loop=0;loop<MAX_PARTICLES;loop++)				// Loop Through All The Particles
  {
    if (particle[loop].active)				// If The Particle Is Active
    {
      float x=particle[loop].x;			// Grab Our Particle X Position
      float y=particle[loop].y;			// Grab Our Particle Y Position
      float z=particle[loop].z;			// Particle Z Pos + Zoom

      // Draw The Particle Using Our RGB Values, Fade The Particle Based On It's Life
      //glColor4f(particle[loop].r,particle[loop].g,particle[loop].b,particle[loop].life);

      glBegin(GL_QUADS);					// Build Quad From A Triangle Strip
      glTexCoord2d(1,1); glVertex3f(x+0.5f,y+0.5f,z);             // Top Right
      glTexCoord2d(0,1); glVertex3f(x-0.5f,y+0.5f,z);         // Top Left
      glTexCoord2d(1,0); glVertex3f(x+0.5f,y-0.5f,z);         // Bottom Right
      glTexCoord2d(0,0); glVertex3f(x-0.5f,y-0.5f,z);         // Bottom Left
      glEnd();							// Done Building Triangle Strip

      particle[loop].x+=particle[loop].xi/(slowdown*1000);            // Move On The X Axis By X Speed
      particle[loop].y+=particle[loop].yi/(slowdown*1000);            // Move On The Y Axis By Y Speed
      particle[loop].z+=particle[loop].zi/(slowdown*1000);            // Move On The Z Axis By Z Speed

      particle[loop].xi+=particle[loop].xg;                           // Take Pull On X Axis Into Account
      particle[loop].yi+=particle[loop].yg;                           // Take Pull On Y Axis Into Account
      particle[loop].zi+=particle[loop].zg;                           // Take Pull On Z Axis Into Account
      particle[loop].life-=particle[loop].fade;                       // Reduce Particles Life By 'Fade'
      glUniform1f(fadeEffect, particle[loop].life);



      //faded = false;

      if (particle[loop].life<0.0f)					// If Particle Is Burned Out
      {
        particle[loop].life=0.0f;				// Give It New Life
        particle[loop].fade=float(rand()%100)/1000.0f+0.003f;	// Random Fade Value
//        particle[loop].x= matrix_[3].x;					// Center On X Axis
//        particle[loop].y= matrix_[3].y;					// Center On Y Axis
//        particle[loop].z= matrix_[3].z;					// Center On Z Axis
        particle[loop].xi=xspeed+float((rand()%60)-32.0f);	// X Axis Speed And Direction
        particle[loop].yi=yspeed+float((rand()%60)-30.0f);	// Y Axis Speed And Direction
        particle[loop].zi=float((rand()%60)-30.0f);             // Z Axis Speed And Direction
        //particle[loop].r=colors[col][0];			// Select Red From Color Table
        //particle[loop].g=colors[col][1];			// Select Green From Color Table
        //particle[loop].b=colors[col][2];			// Select Blue From Color Table
        faded = true;
      }
      //glEnd();
    }
  }
  disableRender();
  //this->allFaded = faded;
}
