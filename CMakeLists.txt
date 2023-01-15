cmake_minimum_required(VERSION 3.7)

project(MoonEngine)

set(SDL2_DIR CACHE STRING "SDL2 include directory (in here you should find lib, include, bin)")
set(SDL2_TTF_DIR CACHE STRING "SDL2_ttf include directory (in here you should find lib, include, bin)")
set(SDL2_MIXER_DIR CACHE STRING "SDL2_mixer include directory (in here you should find lib, include, bin)")
set(SDL2_GPU_DIR CACHE STRING "SDL2_gpu include directory (in here you should find lib, include, bin)")
set(SDL2_IMAGE_DIR CACHE STRING "SDL2_image include directory (in here you should find lib, include, bin)")

set(SDL2_LIBRARIES ${SDL2_DIR}/lib/libSDL2main.a;${SDL2_DIR}/lib/libSDL2.dll.a)
set(SDL2_TTF_LIBRARIES ${SDL2_TTF_DIR}/lib/libSDL2_ttf.dll.a)
set(SDL2_MIXER_LIBRARIES ${SDL2_MIXER_DIR}/lib/libSDL2_mixer.dll.a)
set(SDL2_GPU_LIBRARIES ${SDL2_GPU_DIR}/lib/libSDL2_gpu.dll.a)
set(SDL2_IMAGE_LIBRARIES ${SDL2_IMAGE_DIR}/lib/libSDL2_image.dll.a)

include_directories(${SDL2_DIR}/include/SDL2)
include_directories(${SDL2_TTF_DIR}/include/SDL2)
include_directories(${SDL2_MIXER_DIR}/include/SDL2)
include_directories(${SDL2_GPU_DIR}/include)
include_directories(${SDL2_IMAGE_DIR}/include/SDL2)
include_directories(engine)

add_library(
	libmoon.a STATIC
	engine/3D.c
	engine/Array.c
	engine/Camera.c
	engine/cJSON.c
	engine/Font.c
	engine/Input.c
	engine/Map.c
	engine/Particle.c
	engine/Physics.c
	engine/Rendering.c
	engine/Sound.c
	engine/Sprite.c
	engine/Texture.c
	engine/Time.c
	engine/Timer.c
	engine/UI.c
	engine/Window.c
)

add_executable(
	Example
	main.c
)
target_compile_options(Example PRIVATE -Wall -std=c99)
target_link_libraries(Example libmoon.a ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${SDL2_MIXER_LIBRARIES} ${SDL2_GPU_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

add_custom_command(TARGET Example POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
	"${SDL2_DIR}/bin/SDL2.dll"
	$<TARGET_FILE_DIR:Example>)

add_custom_command(TARGET Example POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
	"${SDL2_TTF_DIR}/bin/SDL2_ttf.dll"
	$<TARGET_FILE_DIR:Example>)

add_custom_command(TARGET Example POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
	"${SDL2_GPU_DIR}/bin/libSDL2_gpu.dll"
	$<TARGET_FILE_DIR:Example>)

add_custom_command(TARGET Example POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
	"${SDL2_MIXER_DIR}/bin/SDL2_mixer.dll"
	$<TARGET_FILE_DIR:Example>)

add_custom_command(TARGET Example POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
	"${SDL2_IMAGE_DIR}/bin/SDL2_image.dll"
	$<TARGET_FILE_DIR:Example>)