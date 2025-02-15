#pragma once

#include <QUndoCommand>
#include <QUndoStack>

#include "tools/cabana/dbc/dbcmanager.h"
#include "tools/cabana/streams/abstractstream.h"

class EditMsgCommand : public QUndoCommand {
public:
  EditMsgCommand(const MessageId &id, const QString &name, int size, const QString &comment, QUndoCommand *parent = nullptr);
  void undo() override;
  void redo() override;

private:
  const MessageId id;
  QString old_name, new_name, old_comment, new_comment;
  int old_size = 0, new_size = 0;
};

class RemoveMsgCommand : public QUndoCommand {
public:
  RemoveMsgCommand(const MessageId &id, QUndoCommand *parent = nullptr);
  void undo() override;
  void redo() override;

private:
  const MessageId id;
  cabana::Msg message;
};

class AddSigCommand : public QUndoCommand {
public:
  AddSigCommand(const MessageId &id, const cabana::Signal &sig, QUndoCommand *parent = nullptr);
  void undo() override;
  void redo() override;

private:
  const MessageId id;
  cabana::Signal signal = {};
};

class RemoveSigCommand : public QUndoCommand {
public:
  RemoveSigCommand(const MessageId &id, const cabana::Signal *sig, QUndoCommand *parent = nullptr);
  void undo() override;
  void redo() override;

private:
  const MessageId id;
  cabana::Signal signal = {};
};

class EditSignalCommand : public QUndoCommand {
public:
  EditSignalCommand(const MessageId &id, const cabana::Signal *sig, const cabana::Signal &new_sig, QUndoCommand *parent = nullptr);
  void undo() override;
  void redo() override;

private:
  const MessageId id;
  cabana::Signal old_signal = {};
  cabana::Signal new_signal = {};
};

namespace UndoStack {
  QUndoStack *instance();
  inline void push(QUndoCommand *cmd) { instance()->push(cmd); }
};
