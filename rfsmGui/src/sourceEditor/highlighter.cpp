/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "highlighter.h"

//! [0]
Highlighter::Highlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;


    keywordRFSMFormat.setForeground(Qt::darkMagenta);
    keywordRFSMFormat.setFontWeight(QFont::Bold);
    keywordRFSMFormat.setFontItalic(true);
    QStringList keywordRFSMPatterns;
    keywordRFSMPatterns << "\\brfsm.state\\b" << "\\brfsm.csta\\b" << "\\brfsm.sista\\b"
                        << "\\brfsm.transition\\b"<< "\\brfsm.conn\\b"<< "\\brfsm.connector\\b"
                        << "\\bsrc\\b" << "\\btgt\\b" << "\\brfsm.trans\\b"
                        << "\\bevents\\b" << "\\bguard\\b" << "\\beffect\\b"
                        << "\\bentry\\b" << "\\bdoo\\b" << "\\bexit\\b" << "\\bpn\\b" ;
    foreach (const QString &pattern, keywordRFSMPatterns) {
        rule.pattern = QRegExp(pattern);
        rule.format = keywordRFSMFormat;
        highlightingRules.append(rule);
    }

    keywordFormat.setForeground(Qt::darkBlue);
    keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns;
    keywordPatterns << "\\band\\b" << "\\bbreak\\b" << "\\bdo\\b"
                    << "\\belse\\b" << "\\belseif\\b" << "\\bend\\b"
                    << "\\bfalse\\b" << "\\btrue\\b" << "\\bfor\\b"
                    << "\\bfunction\\b" << "\\if\\b" << "\\bin\\b"
                    << "\\blocal\\b" << "\\bnil\\b" << "\\bnot\\b"
                    << "\\bor\\b" << "\\brepeat\\b" << "\\breturn\\b"
                    << "\\bthen\\b" << "\\btrue\\b" << "\\buntil\\b"
                    << "\\bwhile\\b";
    foreach (const QString &pattern, keywordPatterns) {
        rule.pattern = QRegExp(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    // state names
    //stateFormat.setFontItalic(true);
    //stateFormat.setForeground(Qt::red);
    //rule.pattern = QRegExp(".+?(?=\\s*=\\s*rfsm.)");
    //rule.format = stateFormat;
    //highlightingRules.append(rule);

    //functions
    functionFormat.setFontItalic(false);
    functionFormat.setForeground(Qt::blue);
    rule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
    rule.format = functionFormat;
    highlightingRules.append(rule);

    // string quatations
    quotationFormat.setForeground(Qt::darkGreen);
    rule.pattern = QRegExp("\"([^\"]*)\"");
    rule.format = quotationFormat;
    highlightingRules.append(rule);
    rule.pattern = QRegExp("\'([^\']*)\'");
    rule.format = quotationFormat;
    highlightingRules.append(rule);


    multiLineCommentFormat.setForeground(Qt::gray);
//    rule.pattern = QRegExp("/--\[\[([^]*)\\]\\]--");
//    rule.format = multiLineCommentFormat;
//    highlightingRules.append(rule);

    singleLineCommentFormat.setForeground(Qt::gray);
    rule.pattern = QRegExp("--[^\n]*");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    commentStartExpression = QRegExp("--\\[\\[");
    commentEndExpression = QRegExp("\\]\\]");
}


void Highlighter::highlightBlock(const QString &text)
{
    foreach (const HighlightingRule &rule, highlightingRules) {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0) {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }
    setCurrentBlockState(0);
    int startIndex = 0;
    if (previousBlockState() != 1)
        startIndex = commentStartExpression.indexIn(text);

    while (startIndex >= 0) {
        int endIndex = commentEndExpression.indexIn(text, startIndex);
        int commentLength;
        if (endIndex == -1) {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else {
            commentLength = endIndex - startIndex
                            + commentEndExpression.matchedLength();
        }
        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = commentStartExpression.indexIn(text, startIndex + commentLength);
    }

}
