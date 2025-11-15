#include <string>
#include <vector>
#include <memory>
#include <imgui.h>
#include <log4cpp/Category.hh>

namespace marmot
{
    struct EditableHeader
    {
        std::string name = "Ma section";
        bool editing = false;
        bool requestFocus = false;
        char buffer[128]{};
    };

    class EditorModel
    {
    public:
        EditorModel(log4cpp::Category &logger) : _logger(logger) {}
        virtual ~EditorModel() {}
        void display();

    private:
        log4cpp::Category &_logger;
        std::vector < std::unique_ptr <EditableHeader> > _sprites;
    };

}
