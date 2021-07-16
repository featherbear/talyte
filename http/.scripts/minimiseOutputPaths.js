'use strict'

const path = require('path')
const fs = require('fs')

let clientRegexer = /\/client\//g
let legacyRegexer = /\/legacy\//g

const processDir = dir => {
  let files = fs.readdirSync(dir)

  files.forEach(file => {
    // First pass, check for /client/ or /legacy/
    let _path = path.join(dir, file)

    if (fs.statSync(_path).isFile()) {
      if (file.endsWith('.js') || file.endsWith('.html')) {
        let contents = fs.readFileSync(_path).toString()

        let changed = false
        if (clientRegexer.test(contents)) {
          contents = contents.replace(clientRegexer, '/c/')
          changed = true
        }
        if (legacyRegexer.test(contents)) {
          contents = contents.replace(legacyRegexer, '/l/')
          changed = true
        }

        if (changed) {
          fs.writeFileSync(_path, contents)
        }
      }
    } else {
      // Recurse first
      processDir(_path)
      let legacyRegexer = /(.*)legacy$/g
      let clientRegexer = /(.*)client$/g
      if (legacyRegexer.test(_path))
        fs.renameSync(_path, _path.replace(legacyRegexer, '$1l'))
      if (clientRegexer.test(_path))
        fs.renameSync(_path, _path.replace(clientRegexer, '$1c'))
    }
  })
}

processDir(path.join(__dirname, '../__sapper__/export'))
console.info("Sapper paths minimised!");
