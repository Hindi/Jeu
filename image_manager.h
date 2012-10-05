#ifndef IMAGE_MANAGER_H_INCLUDED
#define IMAGE_MANAGER_H_INCLUDED

class image_manager
{
    public:
        //Va chercher le fichier et stocke l'image dans une liste
        const sf::Image& getImage( const std::string& filename );

        //Suprimme une image dans la liste
        void  deleteImage( const sf::Image& image );
        void  deleteImage( const std::string& filename );

        //Ajoute un dosier de recherche
        void  addResourceDirectory( const std::string& directory );

        //suprimme un dossier de recherche
        void  removeResourceDirectory( const std::string& directory );


        static void kill();
        static image_manager* getInstance();

    private:
        //Image manager
        image_manager& operator =( const image_manager& );

        //Liste d'images avec le nom
        std::map< std::string, sf::Image > m_images;

        //Liste des répertoires
        std::vector< std::string > m_directories;

        image_manager();

        //Destructeur
        ~image_manager();

        static image_manager* _singleton;
};

image_manager* image_manager::_singleton = NULL;

#endif
