#ifndef NSU_OOP_2021_LABS_WORKFLOWCONFIGURATION_H
#define NSU_OOP_2021_LABS_WORKFLOWCONFIGURATION_H

#include <map>
#include <string>
#include <list>
#include <vector>
#include <fstream>
#include <sstream>

#include "WorkflowParseException.h"
#include "WorkflowIOException.h"

class WorkflowConfigurationParser {
private:
    // mapping id to block body
    std::map<int, std::vector<std::string>> blocks;

    // blocks ids in order of execution
    std::list<int> blocksOrder;

public:
    WorkflowConfigurationParser() {
    }

    void loadFromFile(const char *filename) {
        this->clear();

        // stream for the file and string for each line
        std::ifstream file;

        // enable exceptions
        file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try {
            file.open(filename);
        } catch (std::exception &exception) {
            throw WorkflowIOException("Error upon opening the workflow description file.");
        }

        // state machine for configuration file parsing
        const int BEFORE_BLOCKS_SECTION = 0;
        const int IN_BLOCKS_SECTION = 1;
        const int AFTER_BLOCKS_SECTION = 2;
        const int FINAL_STATE = 3;

        // initial state
        int state = BEFORE_BLOCKS_SECTION;

        // looping over each line
        // currentLine is required to be able to throw an informative exception
        // currentLine may be required after the loop
        std::string line;
        unsigned currentLine;
        try {
            for (currentLine = 1; std::getline(file, line); currentLine++) {
                // splitting the line into words ignoring spaces
                std::stringstream lineStream(line);
                std::vector<std::string> words;
                std::string word;
                while (lineStream >> word) {
                    words.push_back(word);
                }

                // ignore empty lines (for instance in the end of the file)
                if (words.empty()) {
                    continue;
                }

                // processing state transitions
                if (state == BEFORE_BLOCKS_SECTION) {
                    // we want to find desc and transition into IN_BLOCKS_SECTION state
                    if (words.size() == 1 && words[0] == "desc") {
                        state = IN_BLOCKS_SECTION;
                    } else {
                        // throw exception: unexpected literal
                        throw WorkflowParseException(currentLine, "Expected \"desc\"");
                    }
                } else if (state == IN_BLOCKS_SECTION) {
                    // we either find a csed literal and transition into AFTER_BLOCKS_SECTION
                    // or process <integer> = <words> block and stay in the same state
                    if (words.size() == 1 && words[0] == "csed") {
                        state = AFTER_BLOCKS_SECTION;
                    } else if (words.size() >= 3 && words[1] == "=") {
                        int blockId;
                        try {
                            // throws std::invalid_argument if fails to parse
                            blockId = std::stoi(words[0]);
                        }
                        catch (std::invalid_argument &exception) {
                            throw WorkflowParseException(currentLine, "Failed to parse the block-id into integer.");
                        }

                        // we may want to override or disallow such syntax
                        if (this->blocks.count(blockId)) {
                            throw WorkflowParseException(currentLine, "Duplicate block-id found.");
                        }

                        for (int i = 2; i < words.size(); ++i) {
                            this->blocks[blockId].push_back(words[i]);
                        }
                    } else {
                        // throw unexpected configuration file format
                        throw WorkflowParseException(currentLine,
                                                     "Expected to find \"csed\" or a block definition in <integer> = <word> ... format.");
                    }
                } else if (state == AFTER_BLOCKS_SECTION) {
                    if (words.size() % 2 != 1) {
                        // throw because there should be an odd number of words
                        // either <integer> or <integer> (-> <integer>)+
                        throw WorkflowParseException(currentLine, "Expected odd number of literals. Dangling '->'?");
                    }

                    for (int i = 0; i < words.size(); ++i) {
                        if (i % 2 == 1) {
                            if (words[i] != "->") {
                                // throw because unexpected format
                                throw WorkflowParseException(currentLine, "Expected to find '->'.");
                            }
                            continue;
                        }

                        int blockId;
                        try {
                            // throw if impossible to parse
                            blockId = stoi(words[i]);
                        } catch (std::invalid_argument &exception) {
                            throw WorkflowParseException(currentLine, "Failed to parse a block-id into integer.");
                        }

                        // does the block-id is defined in the block definition section?
                        if (!this->blocks.count(blockId)) {
                            // throw if block-id is not defined
                            throw WorkflowParseException(currentLine, "Referencing a non-defined block-id.");
                        }

                        this->blocksOrder.push_back(blockId);
                    }

                    state = FINAL_STATE;
                }
            }
        } catch (WorkflowBaseException &exception) {
            throw;
        } catch (std::exception &exception) {
            if (!file.eof()) {
                throw WorkflowIOException("Error upon reading the workflow description file.");
            }
        }

        try {
            file.close();
        } catch (std::exception &exception) {
            throw WorkflowIOException("Error upon closing the workflow description file.");
        }

        if (state != FINAL_STATE) {
            // throw unexpected input
            throw WorkflowParseException(currentLine, "Unexpected end of file. A missing section?");
        }
    }

    void clear() {
        // reset on loading from a new file
        this->blocks.clear();
        this->blocksOrder.clear();
    }

    std::map<int, std::vector<std::string>> getBlocks() const {
        return this->blocks;
    }

    std::list<int> getBlocksOrder() const {
        return this->blocksOrder;
    }

    std::string toString() const {
        std::stringstream stream;
        stream << "desc" << std::endl;
        for (const auto & block : this->blocks) {
            auto blockId = block.first;
            auto blockWords = block.second;
            stream << blockId << " =";
            for (auto &word: blockWords) {
                stream << " " << word;
            }
            stream << std::endl;
        }
        stream << "csed" << std::endl;

        bool firstBlock = true;
        for (const auto &blockId: this->blocksOrder) {
            if (!firstBlock) {
                stream << " -> ";
            }
            stream << blockId;
            firstBlock = false;
        }
        stream << std::endl;

        return stream.str();
    }
};

#endif //NSU_OOP_2021_LABS_WORKFLOWCONFIGURATION_H
