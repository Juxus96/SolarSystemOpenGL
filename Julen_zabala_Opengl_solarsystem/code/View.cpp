
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on march of 2014                                          *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "View.hpp"
#include <SFML/OpenGL.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace example
{

    void gluPerspective(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar)
    {
        GLdouble height = tan(fovY / 360 * 3.1415926535897932384626433832795) * zNear;
        GLdouble width  = height * aspect;

        glFrustum (-width, +width, -height, +height, zNear, zFar);
    }

    View::View(int width, int height)
    {
        light_location[0] =   0.f;
        light_location[1] =  50.f;
        light_location[2] = 100.f;
        light_location[3] =   1.f;
		
		
        glEnable (GL_CULL_FACE);                // Descartar las back faces
		glEnable(GL_DEPTH_TEST);

        glEnable (GL_LIGHTING );                // Activar la iluminación
        glEnable (GL_LIGHT0   );                // Activar la luz 0
                 
        glShadeModel  (GL_FLAT);                // No difuminar el color en el interior de los polígonos

        glPolygonMode (GL_FRONT, GL_FILL);      // Dibujar sólo el borde de los polígonos

        // Activar el antialiasing de líneas:

        glEnable      (GL_BLEND);
        glEnable      (GL_LINE_SMOOTH);
        glHint        (GL_LINE_SMOOTH_HINT, GL_NICEST);
        glBlendFunc   (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Crear los elementos de la escena:
		Sphere sun		= Sphere(0.2f, 10, 20, 0.7f, 0.7f, 0.f);
		Sphere earth	= Sphere(0.05f, 10, 20, 0.f, 0.f, 1.f);
		Sphere moon		= Sphere(0.01f, 10, 20, 1.f, 1.f, 1.f);


		//inicializar los elementos:
		sun.setPosition(0, 0, -10);
		sun.setRotationVector(0, 1, 0);
		sun.setAngularSpeed(0.5f);

		earth.setPosition(1, 0, 0);
		earth.setRotationVector(1, 0, 0);
		earth.setAngularSpeed(0.7f);

		moon.setPosition(0, 0, 0.1);
		//moon.setRotationVector(1, 0, 0);
		//moon.setAngularSpeed(0.1f);

		//crear la jerarquia de escena:
		earth.addChild(moon);
		sun.addChild(earth);

		//añadir el padre de todos a la escena:
		meshes.push_back(sun);
        resize (width, height);

    }

  //  void View::create_sphere (int subdivisions)
  //  {
  //      if (subdivisions < 2)
  //      {
  //          subdivisions = 2;
  //      }

		//sphere.reset(new Sphere(0.2f, subdivisions, subdivisions * 2, 0.7f, 0.7f, 0.f));

  //      //this->subdivisions = subdivisions;
  //  }

    void View::update ()
    {
		for (auto & mesh : meshes)
		{
			mesh.update();
		}
    }

    void View::render ()
    {
        // Resetear la matriz MODELVIEW:

        glLoadIdentity ();

        // Establecer la posición de la luz:

        glLightfv (GL_LIGHT0, GL_POSITION, light_location);

        // Se dibuja la esfera:
		for (auto & mesh : meshes)
		{
			mesh.render ();
		}
    }

    void View::resize (int width, int height)
    {
        glMatrixMode   (GL_PROJECTION);
        glLoadIdentity ();
        gluPerspective (20, GLdouble(width) / height, 1, 15);
        glViewport     (0, 0, width, height);
        glClearColor   (0.f, 0.f, 0.f,  1.f);
        glMatrixMode   (GL_MODELVIEW);
    }

    //void View::on_key (int key_code)
    //{
    //    switch (key_code)
    //    {
    //        case sf::Keyboard::Add:
    //        case sf::Keyboard::Up:
    //        case sf::Keyboard::Right:
    //        {
    //            //create_sphere (++subdivisions);
    //            break;
    //        }

    //        case sf::Keyboard::Subtract:
    //        case sf::Keyboard::Down:
    //        case sf::Keyboard::Left:
    //        {
    //            //create_sphere (--subdivisions);
    //            break;
    //        }
    //    }
    //}

}
