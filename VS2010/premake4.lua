solution("Sandstorms")
	configurations({"Debug", "Release"})

	project("Sandstorms")
		kind("ConsoleApp")
		language("C++")
		files({
			"../include/**.h",
			"../src/**.cpp"
			})
		includedirs({
			"../include",
			"../include/**"
			})
		libdirs({
			"../lib",
			"../lib/**"
			})

		links({
			"SDL",
			"SDL_image",
			"opengl32",
			"TGAEngine"
			})

		configuration("Debug")
			defines({"DEBUG"})

		configuration("Release")
			defines({"NDEBUG"})
