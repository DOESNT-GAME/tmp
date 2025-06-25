#include "singletonclient.h"

SingletonClient* SingletonClient::m_instance = nullptr;

SingletonClient* SingletonClient::instance()
{
    return m_instance;
}

void SingletonClient::setInstance(SingletonClient* instance)
{
    m_instance = instance;
}
