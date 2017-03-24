
SET(MAGICK "ImageMagick")

FIND_PATH(MAGICK_INCLUDE_DIR
  PATHS
  /usr/include
  /usr/local/include
  /opt/local/include
  /usr/share/doc/assimp-utils
  NO_DEFAULT_PATH
)
 

SET (MAGICK_LIBRARIES
  ${LIBMAGICK} 
)

IF(MAGICK_INCLUDE_DIR)
   SET(MAGICK_FOUND TRUE)
ENDIF(MAGICK_INCLUDE_DIR AND MAGICK_LIBRARIES)

IF(MAGICK_FOUND)
  MARK_AS_ADVANCED(MAGICK_INCLUDE_DIR MAGICK_LIBRARIES )
ENDIF(MAGICK_FOUND)