#if defined(BADVPN_BREACTOR_BADVPN) + defined(BADVPN_BREACTOR_GLIB) + defined(BADVPN_BREACTOR_EMSCRIPTEN) != 1
#error No reactor backend or too many reactor backends
#endif
#ifndef BADVPN_BREACTOR_BADVPN
#error Only support BADVPN as reactor backend
#endif

#include "BReactor_badvpn.h"
