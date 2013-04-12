#ifdef _C_PLUGIN
/*******************************************************************************
 *
 * C plugin 
 *
 */

#include <dlfcn.h>

#include "plugin.h"

/**
 *
 */
void proxenet_c_initialize_vm(plugin_t* plugin) 
{
	char* pathname;
	
	pathname = get_plugin_path(plugin->name);
	if (!pathname) {
		xlog(LOG_CRITICAL,"proxenet_c_plugin:get_plugin_path\n");
		goto proxenet_c_initialize_vm_end;
	}
	
	plugin->interpreter = dlopen(pathname, RTLD_NOW);
	if (plugin->interpreter == NULL) {
		xlog(LOG_CRITICAL,"proxenet_c_plugin:dlopen: %s\n", dlerror());
		goto proxenet_c_initialize_vm_end;
	}
	
proxenet_c_initialize_vm_end:
	xfree(pathname);
	return;
}


/**
 *
 */
void proxenet_c_destroy_vm(plugin_t* plugin)
{
	if (plugin->interpreter != NULL) {
		dlclose(plugin->interpreter);
		plugin->interpreter = NULL;
		
	} else {
		xlog(LOG_ERROR, "Trying to destroy uninitialized interpreter\n");
	}
	
}


/**
 *
 */
char* proxenet_c_plugin(plugin_t* plugin, char* request, const char* function_name)
{
#ifdef DEBUG
	xlog( LOG_DEBUG, "[%s] start %s\n", plugin->name, function_name);
#endif
	
	char* (*plugin_func)(char*);
	char* bufres, *ret;
	int buflen;
	
	if (!plugin->interpreter) return request;
	
	// fixme : add mutex ?
	
	plugin_func = dlsym (plugin->interpreter, function_name);
	if (plugin_func==NULL) {
		xlog(LOG_ERROR,"proxenet_c_plugin:dlsym: %s\n", dlerror());
		return request;
	}
	
	ret = (*plugin_func)(request);
	buflen = strlen(ret) + 1;
	bufres = xmalloc(buflen+1);
	memcpy(bufres, ret, buflen);
	printf("bufres: %s\n", bufres);
	
#ifdef DEBUG
	xlog(LOG_DEBUG, "[%s] end %s\n", plugin->name, function_name);
#endif
	return bufres;
}

#endif
