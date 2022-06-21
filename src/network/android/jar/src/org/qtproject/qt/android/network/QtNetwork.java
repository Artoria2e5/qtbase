/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the plugins of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
******************************************************************************/

package org.qtproject.qt.android.network;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.net.ConnectivityManager;
import android.net.Proxy;
import android.net.ProxyInfo;

public class QtNetwork
{
    private static final String LOG_TAG = "QtNetwork";
    private static ProxyReceiver m_proxyReceiver = null;
    private static final Object m_lock = new Object();
    private static ProxyInfo m_proxyInfo = null;

    private static class ProxyReceiver extends BroadcastReceiver
    {
        @Override
        public void onReceive(Context context, Intent intent)
        {
            m_proxyInfo = null;
        }
    }

    private QtNetwork() {}

    public static void registerReceiver(final Context context)
    {
        synchronized (m_lock) {
            if (m_proxyReceiver == null) {
                m_proxyReceiver = new ProxyReceiver();
                IntentFilter intentFilter = new IntentFilter(Proxy.PROXY_CHANGE_ACTION);
                context.registerReceiver(m_proxyReceiver, intentFilter);
            }
        }
    }

    public static void unregisterReceiver(final Context context)
    {
        synchronized (m_lock) {
            if (m_proxyReceiver == null)
                return;

            context.unregisterReceiver(m_proxyReceiver);
        }
    }

    public static ConnectivityManager getConnectivityManager(final Context context)
    {
        return (ConnectivityManager)context.getSystemService(Context.CONNECTIVITY_SERVICE);
    }

    public static ProxyInfo getProxyInfo(final Context context)
    {
        if (m_proxyInfo == null)
            m_proxyInfo = (ProxyInfo)getConnectivityManager(context).getDefaultProxy();
        return m_proxyInfo;
    }
}
