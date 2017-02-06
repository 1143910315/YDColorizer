local loader = {}
local libpath="./plugin/YDColorizer/YDColorizer.dll"
local loadlibfunc=package.loadlib(libpath,"luaopen_luadlllib")
local DY_MATH=loadlibfunc()
loader.load = function(path)
	DY_MATH.start()
	return true
end

loader.unload = function()
	DY_MATH.stop()
end

return loader