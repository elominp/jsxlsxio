const fs = require('fs');
const child_process = require('child_process');

const platform = process.platform;
const arch = process.arch;
const module_name = 'jsxlsxio';
const addon_path = `./prebuilt/${module_name}-${platform}-${arch}.node`;

function addon_directory_creation_error(err) {
   console.error(`${err}: Unable to create destination directory`);
   process.exit(1);
}

fs.access(addon_path, (err) => {
   if (err) {
      console.log(`${err}: Unable to locate prebuilt module, falling back to compiling it`);
      const npm = child_process.spawn('npm', ['run', 'compile']);
      npm.stdout.pipe(process.stdout);
      npm.stderr.pipe(process.stderr);
      npm.on('close', (code) => {
         if (code) {
            console.log('Module compilation failed, it cannot be installed');
            process.exit(code);
         }
      })
   } else {
      fs.mkdir('./build', (err) => {
         if (err) {
            addon_directory_creation_error(err);
         } else {
            fs.mkdir('./build/Release', (err) => {
               if (err) {
                  addon_directory_creation_error(err);
               } else {
                  fs.rename(addon_path, `./build/Release/${module_name}.node`, (err) => {
                     if (err) {
                        console.error(`${err}: Unable to move prebuilt module`);
                        process.exit(1);
                     }
                  });
               }
            });
         }
      });
   }
});
