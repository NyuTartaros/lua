/*
** $Id: ltm.h,v 1.20 2001/01/19 13:20:30 roberto Exp roberto $
** Tag methods
** See Copyright Notice in lua.h
*/

#ifndef ltm_h
#define ltm_h


#include "lobject.h"
#include "lstate.h"

/*
* WARNING: if you change the order of this enumeration,
* grep "ORDER TM"
*/
typedef enum {
  TM_GETTABLE = 0,
  TM_SETTABLE,
  TM_INDEX,
  TM_GETGLOBAL,
  TM_SETGLOBAL,
  TM_ADD,
  TM_SUB,
  TM_MUL,
  TM_DIV,
  TM_POW,
  TM_UNM,
  TM_LT,
  TM_CONCAT,
  TM_GC,
  TM_FUNCTION,
  TM_N		/* number of elements in the enum */
} TMS;



/*
** masks for allowable tag methods
*/
#define HAS_TM_GETGLOBAL(L,t)	(1<<(t) & ((1<<LUA_TUSERDATA) | \
                                           (1<<LUA_TTABLE) | \
                                           (1<<LUA_TNIL)))

#define HAS_TM_SETGLOBAL(L,t)	(1<<(t) & ((1<<LUA_TUSERDATA) | \
                                           (1<<LUA_TTABLE) | \
                                           (1<<LUA_TNIL) | \
                                           (1<<LUA_TFUNCTION)))



struct TM {
  Closure *method[TM_N];
  TString *collected;  /* list of garbage-collected udata with this tag */
};


#define luaT_gettm(G,tag,event) (G->TMtable[tag].method[event])
#define luaT_gettmbyObj(G,o,e)  (luaT_gettm((G),luaT_tag(o),(e)))


#define validtag(G,t) (NUM_TAGS <= (t) && (t) < G->ntag)

extern const char *const luaT_eventname[];


void luaT_init (lua_State *L);
void luaT_realtag (lua_State *L, int tag);
int luaT_tag (const TObject *o);
int luaT_validevent (int t, int e);  /* used by compatibility module */


#endif
