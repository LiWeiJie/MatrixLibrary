option(INSTALL_HEADERS "Install headers." ON)

if(INSTALL_HEADERS)

    install(DIRECTORY . DESTINATION include/ 
        PATTERN "CMakeLists.txt" EXCLUDE
        PATTERN ".gitignore" EXCLUDE)

endif(INSTALL_HEADERS)
