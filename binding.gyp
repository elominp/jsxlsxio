{
	"targets": [
    {
      "target_name": "jsxlsxio",
      "sources": [
				"./lib/src/jsxlsxio_log.c",
				"./lib/src/jsxlsxio_pointers.cpp",
				"./lib/src/jsxlsxio.c",
				"./lib/src/xlsxioread_close.c",
				"./lib/src/xlsxioread_get_version_string.c",
				"./lib/src/xlsxioread_get_version.c",
				"./lib/src/xlsxioread_list_sheets.c",
        "./lib/src/xlsxioread_open.c",
				"./lib/src/xlsxioread_open_filehandle.c",
				"./lib/src/xlsxioread_open_memory.c",
				"./lib/src/xlsxioread_process.c",
				"./lib/src/xlsxioread_sheet_close.c",
				"./lib/src/xlsxioread_sheet_next_cell.c",
				"./lib/src/xlsxioread_sheet_next_cell_datetime.c",
				"./lib/src/xlsxioread_sheet_next_cell_float.c",
				"./lib/src/xlsxioread_sheet_next_cell_int.c",
				"./lib/src/xlsxioread_sheet_next_cell_string.c",
				"./lib/src/xlsxioread_sheet_next_row.c",
				"./lib/src/xlsxioread_sheet_open.c",
				"./lib/src/xlsxioread_sheetlist_close.c",
				"./lib/src/xlsxioread_sheetlist_next.c",
				"./lib/src/xlsxioread_sheetlist_open.c",
				"./lib/src/xlsxiowrite_add_cell_datetime.c",
				"./lib/src/xlsxiowrite_add_cell_float.c",
				"./lib/src/xlsxiowrite_add_cell_int.c",
				"./lib/src/xlsxiowrite_add_cell_string.c",
				"./lib/src/xlsxiowrite_add_column.c",
				"./lib/src/xlsxiowrite_close.c",
				"./lib/src/xlsxiowrite_get_version_string.c",
				"./lib/src/xlsxiowrite_get_version.c",
				"./lib/src/xlsxiowrite_next_row.c",
				"./lib/src/xlsxiowrite_open.c",
				"./lib/src/xlsxiowrite_set_detection_rows.c",
				"./lib/src/xlsxiowrite_set_row_height.c"
      ],
	  	"include_dirs": [
	  		"./lib/include",
				"./deps/include"
	  	],
			"cflags": [
				"-Wall",
				"-Wextra",
				"-O2"
			],
			"cflags_cc": [
				"-std=c++17",
				"-O2",
				"-Wall",
				"-Wextra"
			],
			"defines": [
				"NDEBUG",
				"ASSERTION_EXIT=0",
				"STATIC"
			],
			"conditions": [
				[
					'OS == "mac"',
					{
						"libraries": [
	  	  			"-lxlsxio_read",
							"-lexpat",
							"-lminizip"
	  				],
						"xcode_settings": {
							"OTHER_CFLAGS": [
								"-Wall",
								"-Wextra",
								"-O2",
								"-DNDEBUG",
								"-DASSERTION_EXIT=0",
								"-DSTATIC"
							],
							"OTHER_CPLUSPLUSFLAGS": [
								"-std=c++17",
								"-Wall",
								"-Wextra",
								"-O2",
								"-DNDEBUG",
								"-DASSERTION_EXIT=0",
								"-DSTATIC"
							]
						},
					}
				],
				[
					'OS == "win"',
					{
						"libraries": [
	  	  			"-l../deps/lib/xlsxio_read.lib",
							"-l../deps/lib/xlsxio_write.lib",
							"-l../deps/lib/zlib.lib",
							"-l../deps/lib/expat.lib"
	  				],
						"defines": [
							"NDEBUG",
							"ASSERTION_EXIT=0",
							"STATIC",
							"-NODEFAULTLIB"
						]
					}
				],
				[
					'OS == "linux"',
					{
						"libraries": [
	  	  			"-lxlsxio_read",
							"-lxlsxio_write",
							"-lexpat",
							"-lminizip"
	  				]
					}
				]
			]
		}
	]
}
