#include "pch.h"
#include "extern.h"
#include <cstdlib>

RSA r = RSA();
string g_public = r.getPublic();
string g_private = r.getPrivate();