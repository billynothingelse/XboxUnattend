function(deploy _TARGET _FILE _DEST)
	message(STATUS "Deploying to destination...")

	add_custom_command(
		TARGET ${_TARGET}
		POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy
		${_FILE}
		${_DEST}
	)

	message(STATUS "Successfully copied binary to destination!")

endfunction()