#ifndef IMAGE_MANAGER_H_INCLUDED
#define IMAGE_MANAGER_H_INCLUDED

class image_manager
{
    public:
        image_manager();
        ~image_manager();
        const sf::Image& getImage( const std::string& filename );
        void  deleteImage( const sf::Image& image );
        void  deleteImage( const std::string& filename );
        void  addResourceDirectory( const std::string& directory );
        void  removeResourceDirectory( const std::string& directory );

    private:
        image_manager& operator =( const image_manager& );
        std::map< std::string, sf::Image > m_images;
        std::vector< std::string > m_directories;
};
#endif
