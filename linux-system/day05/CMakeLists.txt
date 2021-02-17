project(linux-system-day05)

add_executable(fork1 fork-share-var.c)
add_executable(zombie zombie.c)
add_executable(wait wait.c)