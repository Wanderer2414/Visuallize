set(LIB ${CMAKE_SOURCE_DIR}/include)

# Virtual lib
add_library(Controller Controller.cpp)
target_include_directories(Controller PUBLIC ${LIB})

add_library(EventHandler EventHandler.cpp)
target_include_directories(EventHandler PUBLIC ${LIB})

#Event
add_library(TextHandler TextboxEventHandler.cpp)
target_include_directories(TextHandler PUBLIC ${LIB})
target_link_libraries(TextHandler EventHandler)

add_library(MouseHandler MouseEventHandler.cpp)
target_include_directories(MouseHandler PUBLIC ${LIB})
target_link_libraries(MouseHandler EventHandler)

# Shape

add_library(Rectangle Rectangle.cpp)
target_include_directories(Rectangle PUBLIC ${LIB})

add_library(RRectangle RoundedRectangle.cpp)
target_include_directories(RRectangle PUBLIC ${LIB})

add_library(Circle Circle.cpp)
target_include_directories(Circle PUBLIC ${LIB})

# Component

add_library(Textbox Textbox.cpp)
target_include_directories(Textbox PUBLIC ${LIB})
target_link_libraries(Textbox TextHandler Controller Rectangle)

add_library(Button Button.cpp)
target_include_directories(Button PUBLIC ${LIB})
target_link_libraries(Button Controller MouseHandler)

add_library(Node Node.cpp)
target_include_directories(Node PUBLIC ${LIB})
target_link_libraries(Node Circle)

add_library(Form Form.cpp)
target_include_directories(Form PUBLIC ${LIB})
target_link_libraries(Form Controller)

add_library(MainForm VisuallizationBST.cpp)
target_include_directories(MainForm PUBLIC ${LIB})
target_link_libraries(MainForm Form Textbox Button RRectangle Node)
