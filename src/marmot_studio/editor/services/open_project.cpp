#include "open_project.h"

using namespace marmot::studio;

void OpenProjectCallback::onSuccess()
{
}

void OpenProjectCallback::onFailed(int err_code) 
{
}

int OpenProjectJob::execute()
{
    _db->open(_path);
    return 0;
}

