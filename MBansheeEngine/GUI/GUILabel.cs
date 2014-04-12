﻿using System;
using System.Runtime.CompilerServices;

namespace BansheeEngine
{
    public sealed class GUILabel : GUIElement
    {
        public GUILabel(GUIContent content, GUIElementStyle style, params GUIOption[] options)
        {
            Internal_CreateInstance(this, content, style, options);
        }

        public void SetContent(GUIContent content)
        {
            Internal_SetContent(mCachedPtr, content);
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void Internal_CreateInstance(GUILabel instance, GUIContent content, GUIElementStyle style, GUIOption[] options);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void Internal_SetContent(IntPtr nativeInstance, GUIContent content);
    }
}
