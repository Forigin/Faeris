
_is_functions = _is_functions or {}
_to_functions = _to_functions or {}
_push_functions = _push_functions or {}

local fsobject= {
	"FsObject",


	"Scheduler",
	"SchedulerTarget",


	-- graphics 
	"FrameBuffer",
	"RenderDevice",
	"RenderTarget",
	"Texture2D",
	"Window",

	-- util 
	"FsArray",
	"FsDict",
	"FsString",
	"FsInteger",
	"FsFloat",


	-- mgr 
	"TextureMgr",
	"ResourceMgr",
	"ProgramSourceMgr",
	"Resource",



	-- scene 
	"Director",
	"Scene",
	"LuaScene",




	-- layer 
	"Layer",
	"Layer2D",
	"LuaLayer2D",

	"ColorLayer",
	"LuaColorLayer",

	--stage 
	"StageElement",


	--entity 
	"Entity",
	"LuaEntity",



	"FontTTF",
	"LabelTTF",
	"LuaLabelTTF",


	"FontBitmap",
	"LabelBitmap",
	"LuaLabelBitmap",

	"Particle2DEffect",
	"LuaParticle2DEffect",

	"Panel",
	"LuaPanel",

	"Quad2D",
	"LuaQuad2D",

	"Sprite2D",
	"LuaSprite2D",

	"VertexPolygon",
	"LuaVertexPolygon",

	"ITransform",
	"Transform",


	-- ui 
	
	"DynamicView",
	"LuaDynamicView",

	"ListView",
	"LuaListView",

	"PressButton",
	"LuaPressButton",

	"ScrollView",
	"LuaScrollView",

	"StateButton",
	"LuaStateButton",

	"ToggleButton",
	"LuaToggleButton",
	
	"UiWidget",
	"LuaUiWidget",



	--sys/event 
	"TouchEventListener",
	"LuaTouchEventListener",
	"SysEventListener",
	"LuaSysEventListener",

	-- dispatcher
	"TouchDispatcher",
	"SysDispatcher",
	"keypadDispatcher",

	--media  
	"AudioEngine",

	--network 
	"HttpEngine",
	"LuaHttpEngine",
	"LuaHttpRequest",

	--extend 
	"SpineSprite",
	"LuaSpineSprite",

	--action 
	"Action",
	"LuaAction",

	"Curve3Action",
	"LuaCurve3Action",

	"FixTimeAction",
	"LuaFixTimeAction",

	"MoveAction",
	"LuaMoveAction",

	"PauseAction",
	"LuaPauseAction",

	"RotateAction",
	"LuaRotateAction",

	"ScaleAction",
	"LuaScaleAction",

	"SeqAction",
	"LuaAction"
}


local fsenums =
{
	"E_EulerOrientType",
	"E_UniformType",
	"E_UniformRef",
	"E_StreamType",
	"E_ProgramFeatureSupport",
	"E_FogType",
	"E_ShadowType",
	"E_BlendEquation",
	"E_BlendFactor",
	"E_DrawMode",
	"E_AnimPlayMode",
	"E_MeshType",
	"E_MorphAnimFlag",
	"E_FileSeek",
	"E_PixelFormat",
	"E_ImageType",
	"E_TextureFilter",
	"E_TextureWrap",
	"E_FrontFace",
	"E_BoneType",
	"E_LightType",
}



-- register FsObject types
for i = 1, #fsobject do
	_push_functions[fsobject[i]] = "toluaext_pushfsobject2"
end

--- register C++11 Strong Enum 
for i=1 , #fsenums do 
	_push_functions[fsenums[i]]="toluaext_pushfsenum"
	_is_functions[fsenums[i]]="toluaext_isenum"
	_to_functions[fsenums[i]]="toluaext_toenum"
end

-- register LUA_FUNCTION, LUA_TABLE, LUA_HANDLE type
_to_functions["LUA_FUNCTION"] = "toluaext_to_luafunction"
_is_functions["LUA_FUNCTION"] = "toluafix_is_luafunction"

_to_functions["LUA_TABLE"] = "toluaext_to_luatable"
_is_functions["LUA_TABLE"] = "toluaext_is_luatable"
_push_functions["LUA_TABLE"] = "toluaext_push_luatable"

local toWrite = {}
local currentString = ''
local out
local WRITE, OUTPUT = write, output

function output(s)
	out = _OUTPUT
	output = OUTPUT -- restore
	output(s)
end

function write(a)
	if out == _OUTPUT then
		currentString = currentString .. a
		if string.sub(currentString,-1) == '\n'  then
			toWrite[#toWrite+1] = currentString
			currentString = ''
		end
	else
		WRITE(a)
	end
end

function post_output_hook(package)
	local result = table.concat(toWrite)
	local function replace(pattern, replacement)
		local k = 0
		local nxt, currentString = 1, ''
		repeat
			local s, e = string.find(result, pattern, nxt, true)
			if e then
				currentString = currentString .. string.sub(result, nxt, s-1) .. replacement
				nxt = e + 1
				k = k + 1
			end
		until not e
		result = currentString..string.sub(result, nxt)
		if k == 0 then print('Pattern not replaced', pattern) end
	end



	replace([[if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !toluaext_is_luatable(tolua_S,2,"LUA_TABLE",0,&tolua_err)))]],
			[[ if((!toluaext_is_luatable(tolua_S,2,"LUA_TABLE",0,&tolua_err)))]])
	replace([[toluaext_push_luatable(tolua_S,(void*)&self->m_scriptData,"LUA_TABLE");]],
	[[toluaext_push_luatable(tolua_S,self->m_scriptData);]]);

	replace([[self->m_scriptData = *((LUA_TABLE*)  toluaext_to_luatable(tolua_S,2,0))]],
	[[if(self->m_scriptData!=-1) 
	{
		toluaext_remove_luatable(tolua_S,self->m_scriptData); 
	}
	self->m_scriptData=toluaext_to_luatable(tolua_S,2,0);
	if(self->m_scriptData==-1)
	{
		lua_pushvalue(tolua_S,TOLUA_NOPEER);
		lua_setfenv(tolua_S,1);
	}
	else 
	{
		toluaext_push_luatable(tolua_S,self->m_scriptData);
		lua_setfenv(tolua_S,1);
	}
	]]
	)

	replace([[tolua_usertype(tolua_S,"LUA_TABLE");]], [[]])


	for i=1,#fsobject do 
		result =string.gsub(result,
		"tolua_cclass%(tolua_S,\"([%w_]*)\",\"("..fsobject[i]..")\",\"([%w_]*)\",NULL",
		"tolua_cclass%(tolua_S,\"%1\",\""..fsobject[i].."\",\"%3\",toluaext_fscollector")
	end 

	for i=1,#fsobject do 
		result=string.gsub(result,
		"tolua_usertype%(tolua_S,\""..fsobject[i].."\"%)",
		"toluaext_usertype(tolua_S,\""..fsobject[i].."\"%)")
	end

	for i=1,#fsenums do 
		result=string.gsub(result,
		"tolua_constant%(tolua_S,(\"[%w_]*\"),("..fsenums[i]..")::([%w_]*)",
		"tolua_constant%(tolua_S,%1,static_cast<int>("..fsenums[i].."::%3)")

		result=string.gsub(result,
		 " tolua_usertype%(tolua_S,\""..fsenums[i].."\"%);\n",
		 "")

		 result=string.gsub(result,
		 "%*%(%("..fsenums[i].."%*%)",
		 "(("..fsenums[i]..")")

	end






	WRITE(result)

end


























