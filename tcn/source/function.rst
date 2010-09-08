===============
TCN功能模块总结
===============

.. index::
    encoder, decoder

encoder/decoder
==================
.. note::

    编解码器的功能包括:负责MVB总线发送从中央处理器接收到数据来,或者相反.

    在编解码器和中央处理器之间使用一种 **握手** 协议.

    编解码器还会向中央处理器报告如下信息: master或者slave帧检测,CS错误,曼彻斯特编码出错等.

    [1]_ p4 说明,当中央处理器发送命令 *Send Slave_Frame* ,编码器的有限自动机会依次生成 *Start_Bit, Slave_Start_Delimiter, Frame_Data, Check_Sequence, End_Delimiter*, 其中的 *Frame_Data* 从FIFO内存中得到,由中央处理器已经写入.

.. image:: ../image/codec.jpg
    :height: 600
    :width: 800
    :align: center
    :alt:   codec
    

.. [1] Slave node architecture for Train Communication Network

