#ifndef WORD_H
#define WORD_H


class Word
{
private:
    std::string text;
    int count;

public:
    Word(const std::string &initWord = "", int initCount = 1);
    std::string getText() const;
    void setText(const std::string &setWord);
    int getCount() const;
    void setCount(int setCount);
    bool operator<(Word const &w) const;
    bool operator!=(Word const &w) const;
};

#endif