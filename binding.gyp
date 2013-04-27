{
	'targets': [
		{
			'target_name': 'barbarian',
			'sources': [
				'src/barbarian.cpp',
				'src/application.cpp',
				'src/client.cpp'
			],
			'defines': [
				'USING_CEF_SHARED'
			],
			'cflags': [
				'-fvisibility-inlines-hidden'
			],
			'include_dirs': [
				'.',
				'<(module_root_dir)/deps/cef'
			],
			'conditions': [
				['OS=="linux"', {
					'defines': [
						'__LINUX__'
					],
					'cflags': [
						'<!@(pkg-config --cflags gtk+-2.0 gthread-2.0)'
					],
					'link_settings': {
						'ldflags': [
							'<!@(pkg-config --libs-only-L --libs-only-other gtk+-2.0 gthread-2.0)',
							'-Wl,-rpath,\'$$ORIGIN/../../deps/cef/\''
						],
						'libraries': [
							'<!@(pkg-config --libs-only-l gtk+-2.0 gthread-2.0)',
							'<(module_root_dir)/deps/cef/libcef.so',
							'<(module_root_dir)/deps/cef/libcef_dll_wrapper.a'
						],
					}
				}]
			]
		}
	]
}
