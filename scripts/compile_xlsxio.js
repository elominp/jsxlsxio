const fs = require('fs');
const child_process = require('child_process');
const cwd = process.cwd();
const prefix = `${cwd}/deps`;
const platform = process.platform;
const build_type = 'Release';
const windows_sdk_version = '10.0.17134.0';
//const windows_sdk_version = '10.0.17763.0';

fs.mkdir('deps', (err) => {
  if (err) {
    console.error(`${err}: Couldn't create deps directory`);
  } else {
    process.chdir('./deps');

    // Compilation of expat library
    child_process.execSync('git clone https://github.com/libexpat/libexpat.git');
    process.chdir('./libexpat/expat');
    fs.mkdirSync('build');
    process.chdir('./build');
    child_process.execSync(`cmake -DCMAKE_INSTALL_PREFIX=${prefix} -DBUILD_doc=OFF -DBUILD_examples=OFF -DBUILD_shared=OFF -DBUILD_tests=OFF -DBUILD_tools=OFF -DCMAKE_BUILD_TYPE=${build_type} ..`);
    if (platform === 'win32') {
      child_process.execSync('msbuild expat.vcxproj');
      child_process.execSync('msbuild INSTALL.vcxproj');
    } else {
      child_process.execSync('make install');
    }
    process.chdir('../../..');

    // Compilation of zlib library
    child_process.execSync('git clone https://github.com/madler/zlib.git');
    process.chdir('./zlib')
    if (platform === 'win32') {
      process.chdir('./contrib/vstudio/vc14');
      child_process.execSync(`msbuild zlibvc.sln /p:Configuration=${build_type};PlatformToolset=v141;WindowsTargetPlatformVersion=${windows_sdk_version}`);
      fs.renameSync('./x64/ZlibStatRelease/zlibstat.lib', `${prefix}/minizip.lib`);
      process.chdir('../../../..');
    } else {
      fs.mkdirSync('./build');
      process.chdir('./build');
      child_process.execSync(`cmake -DCMAKE_INSTALL_PREFIX=${prefix} -DCMAKE_BUILD_TYPE=${build_type} ..`);
      child_process.execSync('make install');
      process.chdir('../..');
    }

    // Compilation of xlsxio library
    if (platform !== 'win32') {
      child_process.execSync('git clone https://github.com/brechtsanders/xlsxio.git');
      process.chdir('./xlsxio');
      fs.mkdirSync('tmp');
      process.chdir('./tmp');
      //child_process.execSync(`cmake -DCMAKE_INSTALL_PREFIX=${prefix} -DBUILD_TOOLS=OFF -DBUILD_EXAMPLES=OFF -DBUILD_SHARED=OFF -DCMAKE_BUILD_TYPE=${build_type} ..`);
      child_process.execSync(`cmake -DCMAKE_INSTALL_PREFIX=${prefix} -DBUILD_TOOLS=OFF -DBUILD_EXAMPLES=OFF -DBUILD_SHARED=OFF -DMINIZIP_LIBRARIES=${prefix}/lib -DMINIZIP_INCLUDE_DIRS=${prefix}/include -DEXPAT_LIBRARY=${prefix} -DCMAKE_BUILD_TYPE=${build_type} ..`);
      if (platform === 'win32') {
        child_process.execSync('msbuild xlsxio_read_STATIC.vcxproj');
        child_process.execSync('msbuild xlsxio_write_STATIC.vcxproj');
        child_process.execSync('msbuild INSTALL.vcxproj');
      } else {
        child_process.execSync('make install');
      }
    }
    else {
      console.log('Not yet supported');
    }
  }
});
