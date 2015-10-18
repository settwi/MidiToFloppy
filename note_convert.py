from __future__ import print_function

# Step between half notes
STEP = 2**(1.0/12)

def noteify(usecdelay, up, down):
    notes = [usecdelay]

    for i in xrange(1, up + 1):
        notes.append(usecdelay / (pow(STEP, i)))

    for i in xrange(1, down + 1):
        notes.insert(0, usecdelay * (pow(STEP, i)))

    return notes

if __name__ == '__main__':
    # Delay between motor pulses at defined note
    # This default one is A4.
    # Up and down determine its absolute position
    freq = 4550

    # Notes to go up, and down, from specified frequency
    # This way, we have all 127 (!) MIDI notes covered.
    down, up = 57, 52

    # Starting index in list of notes
    # Default is 9 for note A0.
    # Should suffice.
    # offset = 9
    print_file = open("notes.h", "wb+")

    notes = noteify(freq, up, down)
    notenames = (
        "C", "CS", "D", "DS",
        "E", "F", "FS", "G",
        "GS", "A", "AS", "B"
    )
    print(
        "/*\n"
        " * MIDI Notes of floppy frequencies.\n"
        " * 'Author:' William Setterberg (settwi)\n"
        " * Generated with note_convert.py\n"
        " */\n\n"
        "// These values are never technically notes.\n"
        "#define REST 1\n"
        "#define DONE 0\n",
        file=print_file)

    # It feels funny writing a C file in Python.
    for i, note in enumerate(notes):
        print(
            "#define {}_{} {}".format(
                notenames[i%12],
                (i) / 12,
                int(round(note))
                ),
            file=print_file
            )

    print_file.close()

