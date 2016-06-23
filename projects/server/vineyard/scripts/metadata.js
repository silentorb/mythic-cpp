// Generates simple C++ data structure metadata

var fs = require('fs')

var configuration = {
    "builds": [
        {}
    ]
}

var configuration_sample = {
    "builds": [
        {
            "inputs": [
                "path_to_header.h"
            ],
            "output": {
                "file": "path_to_header.h",
                "function": "generate_trellises"
            }

        }
    ]
}

function process_command_line_arguments() {
    var actions = {
        '-c': function (value) {
            configuration = fs.readFileSync(value, 'utf8')
        }
    }

    for (var i = 0; i < process.argv.length; i += 2) {
        var flag = process.argv[i]
        if (!actions[value]) {
            console.error('Invalid flag: ' + flag)
            process.exit()
        }

        var value = process.argv[i + 1]
        if (!value) {
            console.error('Flag is missing value: ' + flag)
            process.exit()
        }

        actions [flag](value)
    }
}

function parse_source(source) {

}

function generate_header(output, classes) {
    var content = ''
    fs.writeFileSync(output.filename, content, 'utf8')
}

function run_build(build) {
    var classes = []
    for (var i in build.inputs) {
        var source = fs.readFileSync(build.inputs, 'utf8')
        var data = parse_source(source)
        classes.push(data)
    }

    generate_header(build.output, classes)
}

function run() {
    process_command_line_arguments()

    for (var i in configuration.builds) {
        var build = builds[i]
        run_build(build)
    }
}

run()