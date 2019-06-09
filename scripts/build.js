const fs = require('fs');
const child_process = require('child_process');
const https = require('https')

const platform = process.platform;
const arch = process.arch;
const module_name = 'jsxlsxio';
const addon_name = `${module_name}-${platform}-${arch}.node`;
const version = "0.2.0";

function onInstallFailure(err) {
    console.log(`${err}: Unable to install prebuilt module, falling back to compiling it`);
    const npm = child_process.spawn('npm', ['run', 'compile']);
    npm.stdout.pipe(process.stdout);
    npm.stderr.pipe(process.stderr);
    npm.on('close', (code) => {
        if (code) {
            console.log('Module compilation failed, it cannot be installed');
            process.exit(code);
        }
    })
}

function addon_directory_creation_error(err) {
    console.error(`${err}: Unable to create destination directory`);
    onInstallFailure(err);
}

fs.mkdir('./build', (err) => {
    if (err) {
        addon_directory_creation_error(err);
    } else {
        fs.mkdir('./build/Release', (err) => {
            if (err) {
                addon_directory_creation_error(err);
            } else {
                const addon_path = `${module_name}.node`;
                const dest_file = fs.createWriteStream(addon_path);
                const addon = https.get(`https://elominp.fr/files/${module_name}/${version}/${addon_name}`, (response) => {
                    dest_file.on('finish', (err) => {
                        if (err) {
                            console.error(`${err}: Unable to download the prebuilt module`);
                            onInstallFailure(err);
                        }
                        fs.rename(addon_path, `./build/Release/${addon_path}`, (err) => {
                            if (err) {
                                console.error(`${err}: Unable to move prebuilt module`);
                                onInstallFailure(err);
                            }
                        });
                    });
                    response.pipe(dest_file);
                });
            }
        });
    }
});
