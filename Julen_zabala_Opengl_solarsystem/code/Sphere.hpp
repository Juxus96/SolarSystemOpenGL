
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on march of 2014                                          *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef SPHERE_HEADER
#define SPHERE_HEADER

    #include <vector>

    namespace example
    {

        class Sphere
        {
        private:

            // Características de la aproximación a la esfera:

            struct Features
            {
                float radius;
                int   number_of_bands;      // Numéro de bandas paralelas al ecuador
                int   number_of_slices;     // Número de secciones de polo a polo
            };

            // Coordenadas de un punto o de un vector:

            struct Coordinates
            {
                enum
                {
                    X, Y, Z
                };

                float values[3];

                Coordinates()
                {
                }

                Coordinates(float x, float y, float z)
                {
                    values[X] = x;
                    values[Y] = y;
                    values[Z] = z;
                }
            };

            // Tipos de contenedores:

            typedef std::vector< Coordinates  > Coordinates_Buffer;     // Lista de coordenadas
            typedef std::vector< unsigned int > Index_Buffer;           // Lista de índices
            typedef std::vector< Index_Buffer > Index_Buffer_Set;       // Grupo de listas de índices
            typedef std::vector< Sphere		  > Children;				// Hijos en la escena

        private:

            Features           features;		// Características de la aproximación a la esfera
            Coordinates_Buffer vertices;		// Lista de vértices (compartidos entre varios triángulos)
            Coordinates_Buffer normals;			// Lista de normales de cada vértice
            Index_Buffer_Set   bands;			// Bufers de índices de triangle strips de bandas (uno por cada banda)
            Index_Buffer_Set   caps;			// Bufers de índices de triangle fans de tapas (uno por cada tapa)
			float			   color[3];		// Color de la esfera
			Coordinates		   position;		// Position of the Sphere
			Coordinates		   rotationVector;	// The vector of the rotation
			float			   angle = 0;		// The angle of the rotation
			float			   angularSpeed;	// The angular speed
			Children		   children;		// hijos del transform de la esfera

        public:

			Sphere(float radius, int number_of_bands = 10, int number_of_slices = 20, float r = 0, float g = 0, float b = 0);

            void render ();
			void update();

			inline void addChild(Sphere child) { children.push_back(child); }
			inline void setAngularSpeed(float value) { angularSpeed = value; }
			inline void setPosition(float x, float y, float z) { position.values[0] = x; position.values[1] = y; position.values[2] = z; }
			inline void setRotationVector(float x, float y, float z) { rotationVector.values[0] = x; rotationVector.values[1] = y; rotationVector.values[2] = z; }

        private:

            void cache_geometry ();
            void cache_point    (const float alpha, const float beta);
            void cache_ring     (const float beta);
            void cache_normals  ();
            void weave_cap      (int tip_index, int ring_start_index, int step);
            void weave_band     (int band_a_start_index, int band_b_start_index);

        };

    }

#endif
