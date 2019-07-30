#ifndef Engine_Include_h__
#define Engine_Inlcude_h__

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC 
#include <stdlib.h> 
#include <crtdbg.h>
#endif

#include <d3d9.h>
#include <d3dx9.h>

#ifdef _DEBUG 
#ifndef DBG_NEW 
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW 
#endif 
#endif  // _DEBUG  


#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <functional>
#include <math.h>

#include "Engine_Struct.h"
#include "Engine_Macro.h"
#include "Engine_Function.h"

using namespace std;

#endif