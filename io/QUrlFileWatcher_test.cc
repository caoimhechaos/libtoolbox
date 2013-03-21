/*
 * Tests for the QUrl file watcher
 *
 * Created on: Dec 12, 2012
 *     Author: Caoimhe Clausen
 */

#include <QtCore/QCoreApplication>
#include <QtCore/QTemporaryFile>
#include <QtCore/QThread>
#include <QtCore/QUrl>
#include <gtest/gtest.h>
#include <string>

#include "toolbox/io/QUrlFileWatcher.h"

namespace toolbox {
namespace io {
namespace testing {

class Receiver : public QUrlFileWatcherNotificationReceiver
{
public:
	Receiver(QByteArray* dest)
	: dest_(dest)
	{
		dest->clear();
	}

	virtual void Receive(int64_t revision, const QByteArray& data)
	{
		dest_->clear();
		dest_->append(data);
	}

protected:
	QByteArray* dest_;
};

class QUrlFileWatcherTest : public ::testing::Test {
protected:
	virtual void SetUp()
	{
	}

	virtual void TearDown()
	{
	}
};

TEST_F(QUrlFileWatcherTest, TestTempFile)
{
	QTemporaryFile f;
	QUrl url;
	QByteArray buf;

	Receiver r(&buf);

	f.open();
	url.setScheme("file");
	url.setPath(f.fileName());
	f.close();

	QUrlFileWatcher watcher(url, &r);
	f.open();
	f.write("test");
	f.close();
	QThread::yieldCurrentThread();

	EXPECT_EQ("test", QString(buf).toStdString());
}

}  // namespace testing
}  // namespace io
}  // namespace toolbox
