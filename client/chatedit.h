/**************************************************************************
 *                                                                        *
 * SPDX-FileCopyrightText: 2017 Kitsune Ral <kitsune-ral@users.sf.net>
 *                                                                        *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *                                                                        *
 **************************************************************************/

#pragma once

#include "kchatedit.h"

#include <QtGui/QTextCursor>

class ChatRoomWidget;

class ChatEdit : public KChatEdit
{
        Q_OBJECT
    public:
        using completions_t = QVector<QPair<QString, QUrl>>;

        ChatEdit(ChatRoomWidget* c);

        void triggerCompletion();
        void cancelCompletion();
        bool isCompletionActive();

        void insertMention(QString author, QUrl url);

    public slots:
        void switchContext(QObject* contextKey) override;
        void alternatePaste();

    signals:
        void proposedCompletion(const QStringList& allCompletions, int curIndex);
        void cancelledCompletion();
        void insertImageRequested(const QImage& image);
        void attachFileRequested(const QString& localPath);

    protected:
        bool canInsertFromMimeData(const QMimeData* source) const override;
        void insertFromMimeData(const QMimeData* source) override;

    private:
        ChatRoomWidget* chatRoomWidget;

        QTextCursor completionCursor;
        /// Text/href pairs for completion
        completions_t completionMatches;
        int matchesListPosition;

        bool pickingMentions = false;
        bool m_pastePlaintext;

        /// \brief Initialise a new completion
        ///
        /// \return true if completion matches exist for the current entry;
        ///         false otherwise
        bool initCompletion();
        void appendMentionAt(QTextCursor& cursor, QString mention,
                             QUrl mentionUrl, bool select);
        void keyPressEvent(QKeyEvent* event) override;
        void contextMenuEvent(QContextMenuEvent* event) override;
        bool pastePlaintextByDefault();
};


