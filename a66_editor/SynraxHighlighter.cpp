#include "SyntaxHighlighter.h"
#include <QTextDocument>
#include <QColor>

SyntaxHighlighter::SyntaxHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent) {
    HighlightingRule rule;

    // 关键字高亮规则
    keywordFormat.setForeground(Qt::red); // 使用橙色高亮
    QStringList keyWords = {
        "def", "if", "else", "while", "for", "in", "println", "print", "scanf", "global",
        "{", "}", ";", ",", ":", "return"
    };
    QString keywordPattern;
    for (const QString &keyword : keyWords) {
        if (!keywordPattern.isEmpty()) {
            keywordPattern += "|";
        }
        keywordPattern += "\\b" + QRegExp::escape(keyword) + "\\b";
    }
    rule.pattern = QRegExp(keywordPattern);
    rule.format = keywordFormat;
    highlightingRules.append(rule);

    // 运算符高亮规则
    operatorFormat.setForeground(Qt::blue); // 使用蓝色高亮
    QStringList operators = {
        "&&", "||", "++", "--", "<=", ">=", "==", "!=", "+", "-", "*", "/", ">", "<", "=",
        "%", "!", "(", ")", "len", "[", "]"
    };
    QString operatorPattern;
    for (const QString &op : operators) {
        if (!operatorPattern.isEmpty()) {
            operatorPattern += "|";
        }
        operatorPattern += QRegExp::escape(op);
    }
    rule.pattern = QRegExp(operatorPattern);
    rule.format = operatorFormat;
    highlightingRules.append(rule);
}

void SyntaxHighlighter::highlightBlock(const QString &text) {
    foreach (const HighlightingRule &rule, highlightingRules) {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0) {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }
}
