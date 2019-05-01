### Submods

## Blaze math package
#add_subdirectory(blaze)

## Merseburg integration
#add_subdirectory(merseburg-incantation)

message("*** ${CMAKE_CURRENT_SOURCE_DIR}/merseburg-incantation/include/header")

# We make these includes available to the parent scope
# TODO: We should use Find cmake module semantics for this instead!!!
set(MGS_SUBMOD_INCLUDES
  ${CMAKE_CURRENT_SOURCE_DIR}/merseburg-incantation/include/header
  ${CMAKE_CURRENT_SOURCE_DIR}/merseburg-incantation/include
  PARENT_SCOPE)
