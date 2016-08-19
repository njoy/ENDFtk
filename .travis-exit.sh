if [ "${TRAVIS_PULL_REQUEST}" = "false" ] && ([ ! -z ${SANITIZER+x} ] || [ "build_type" = "release" ]) 
then
    echo "Builds and tests with release and sanitizer options are only run during pull requests"
    export SHOULD_QUIT="true"
fi
