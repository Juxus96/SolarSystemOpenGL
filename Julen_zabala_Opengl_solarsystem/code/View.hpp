
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on march of 2014                                          *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef VIEW_HEADER
#define VIEW_HEADER

    #include <memory>
    #include "Sphere.hpp"

    namespace example
    {

        class View
        {
        private:

            std::vector< Sphere > meshes;

            float light_location[4];
            //int subdivisions;

        public:

            View(int width, int height);

            //void create_sphere (int subdivisions);

            void update ();
            void render ();
            void resize (int width, int height);
            //void on_key (int key_code);

        };

    }

#endif
