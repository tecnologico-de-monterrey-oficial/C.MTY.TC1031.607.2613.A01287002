# finalize_hashes.cmake

set(HASH_FILE "${RELEASE_DIR}/hash.txt")

# Convert comma-separated string back to a CMake list
string(REPLACE "," ";" TARGET_LIST "${TARGET_NAMES}")

# Read existing hash records
if(EXISTS "${HASH_FILE}")
    file(READ "${HASH_FILE}" OLD_CONTENTS)
else()
    set(OLD_CONTENTS "")
endif()

set(NEW_CONTENTS "")
set(HAS_CHANGES FALSE)

foreach(TARGET_NAME IN LISTS TARGET_LIST)
    if(WIN32)
        set(BIN_PATH "${RELEASE_DIR}/${TARGET_NAME}.exe")
    else()
        set(BIN_PATH "${RELEASE_DIR}/${TARGET_NAME}")
    endif()

    if(EXISTS "${BIN_PATH}")
        file(SHA256 "${BIN_PATH}" CURRENT_HASH)
        string(APPEND NEW_CONTENTS "${TARGET_NAME}: ${CURRENT_HASH}\n")

        # Compare current hash against existing hash.txt entries
        string(FIND "${OLD_CONTENTS}" "${CURRENT_HASH}" HASH_INDEX)
        if(HASH_INDEX EQUAL -1)
            set(HAS_CHANGES TRUE)
            message(STATUS "[Hash Check] New/Updated binary detected for '${TARGET_NAME}': ${CURRENT_HASH}")
        else()
            message(STATUS "[Hash Check] Target '${TARGET_NAME}' hash matches existing record.")
        endif()
    else()
        message(WARNING "[Hash Check] Executable not found: ${BIN_PATH}")
    endif()
endforeach()

# Overwrite hash.txt only after processing all executables
if(HAS_CHANGES OR NOT EXISTS "${HASH_FILE}")
    file(WRITE "${HASH_FILE}" "${NEW_CONTENTS}")
    message(STATUS "[Hash Check] Updated ${HASH_FILE} with all current hashes.")
else()
    message(STATUS "[Hash Check] No binary changes detected. ${HASH_FILE} remains unchanged.")
endif()