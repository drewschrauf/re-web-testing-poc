# reweb-testing-example


[![CircleCI](https://circleci.com/gh/yourgithubhandle/reweb-testing-example/tree/master.svg?style=svg)](https://circleci.com/gh/yourgithubhandle/reweb-testing-example/tree/master)


**Contains the following libraries and executables:**

```
reweb-testing-example@0.0.0
│
├─test/
│   name:    TestRewebTestingExample.exe
│   main:    TestRewebTestingExample
│   require: reweb-testing-example.lib
│
├─library/
│   library name: reweb-testing-example.lib
│   namespace:    RewebTestingExample
│   require:
│
└─executable/
    name:    RewebTestingExampleApp.exe
    main:    RewebTestingExampleApp
    require: reweb-testing-example.lib
```

## Developing:

```
npm install -g esy
git clone <this-repo>
esy install
esy build
```

## Running Binary:

After building the project, you can run the main binary that is produced.

```
esy x RewebTestingExampleApp.exe 
```

## Running Tests:

```
# Runs the "test" command in `package.json`.
esy test
```
