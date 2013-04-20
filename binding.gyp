{
	'targets': [
		{
			'target_name': 'barbarian',
			'sources': [
				'src/barbarian.cpp'
			],
			'conditions': [
				['OS=="linux"', {
					'defines': [
						'__LINUX__'
					],
					'cflags': [
						'<!@(pkg-config --cflags gtk+-2.0 gthread-2.0)',
						'-I<(module_root_dir)/deps/cef'
					],
					'ldflags': [
						'<!@(pkg-config  --libs-only-L --libs-only-other gtk+-2.0 gthread-2.0)',
						'<(module_root_dir)/deps/cef/libcef.so',
						'-Wl,-R,\'<(module_root_dir)/deps/cef/\''
					],
					'libraries': [
						'<!@(pkg-config  --libs-only-l --libs-only-other gtk+-2.0 gthread-2.0)'
					],
				}]
			]
		}
	]
}
