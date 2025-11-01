🎵 MP3 Tag Reader & Editor (C CLI Tool)

A lightweight command-line utility written in C to read and edit ID3 metadata in MP3 files. Supports fields like Title, Artist, Album, Year, Comment, and Genre, with safe binary parsing and endian-aware tag handling.

✨ Features

✅ View MP3 ID3 tags

✏️ Edit metadata fields safely

🧠 Validates MP3 file format

🔁 Endian-safe tag updates

🧱 Modular code structure (view/edit modules)

📑 Help menu for command usage

💡 CLI-based — no GUI required


📂 Project Structure
.
├── mp3_main.c
├── mp3_header.h
├── mp3_view.c
├── mp3_edit.c
└── screenshots/
    ├── mp3_edit.png
    ├── mp3_view.png
    └── mp3_help.png

🚀 Usage
  View MP3 tags  :  ./a.out -v <file_name>
  Edit MP3 tags  :  ./a.out -e <tag_option> <new_value> <file_name>
  Help           :  ./a.out --help


📌 Commands Reference

| Option   | Meaning       |
| -------- | ------------- |
| `-v`     | View MP3 tags |
| `-e`     | Edit MP3 tags |
| `-t`     | Title         |
| `-a`     | Artist        |
| `-A`     | Album         |
| `-y`     | Year          |
| `-c`     | Comment       |
| `-g`     | Genre         |
| `--help` | Show help     |

🛠 Skills Demonstrated

File I/O (binary mode)

Endian conversions

String & pointer manipulation

Modular C programming

CLI interface design

📸 Sample Output

✅ Viewing Tags
=============================================================
                 MP3 TAG READER AND EDITOR
=============================================================

Tag Name             | Tag Value
-------------------------------------------------------------
Title                | Perfect
Artist               | Ed Sheeran
Album                | Divide
Year                 | 2017
Comment              | Love Song
Music                | Pop
-------------------------------------------------------------


✅ Editing Tag
-------------------------------------------------------------
Tag 'TIT2' updated successfully!!!
-------------------------------------------------------------

⭐ Learning Outcomes

Understanding MP3 file structure & ID3 tags

Working with binary files

Byte order conversion

Parsing and modifying file metadata

Command-line argument handling

Memory & pointer handling

👤 Author

Kannan D S
Emertxe Information Technologies


