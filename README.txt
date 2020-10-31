Name: Justin Kim
Uni: jyk2149

Create Tree:
    (from base dir)
    ./create-tree.sh [email tree name]

Install:
    (from base dir)
    make install DEST=./[email tree name]

Run Program:
    (from tree dir)
    bin/mail-in < [input file]

Run Tests:
    (from base dir)
    ./test.sh [email tree name]

    OR

    make test ---> This creates a new email tree called "email_system"


Notes:
    - When there is an invalid sender name, it prints to stderr but still moves on.
      I saw a couple differing things from the prompt vs piazza, but i think most recent
      asked for this.

    - There doesn't seem to be a limit on message length, because strings in c++ don't seem to have a limit
    
